import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session,url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import date

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    users = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])
    owned_cash = users[0]['cash']

    # Get user currently owned stocks
    quotes = db.execute("""SELECT *, purchase_price * shares AS total
                            FROM quotes
                            WHERE user_id = ?
                            GROUP BY user_id,quote_name,quote_symbol
                            HAVING shares > 0;""", session["user_id"])

    # Use lookup API to get the current price for each stock
    quotes = [dict(x, **{'purchase_price': lookup(x['quote_symbol'])['price']}) for x in quotes]

    # Calcuate total price for each stock
    quotes = [dict(x, **{'total': x['purchase_price']*x['shares']}) for x in quotes]

    sum_totals = owned_cash + sum([x['total'] for x in quotes])

    return render_template("index.html", owned_cash=owned_cash, quotes=quotes, sum_totals=sum_totals)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if not (quote_symbol := request.form.get("symbol")):
            return apology("MISSING SYMBOL")

        if not (number := request.form.get("shares")):
            return apology("MISSING SHARES")

        try:
            number = int(number)
        except ValueError:
            return apology("INVALID SHARES")


        if not (number > 0):
            return apology("INVALID SHARES")

        # Ensure symbol is valided
        if not (quote := lookup(quote_symbol)):
            return apology("INVALID SYMBOL")


        rows = db.execute ("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        total_price = quote["price"] * number
        user_cash = rows[0]["cash"]

        if user_cash < total_price:
            return apology("You dont have enough cash to buy ")

                # Check if the user already owns the stock
        rows = db.execute("SELECT * FROM quotes WHERE user_id = ? AND quote_symbol = ?", session["user_id"], quote_symbol)

        # If not, insert a new row
        if len(rows) == 0:
            db.execute("INSERT INTO quotes VALUES (?,?,?,?,?);",session["user_id"], quote["name"], quote["symbol"], number, quote["price"])

        # If yes, update the existing row
        else:
            db.execute("UPDATE quotes SET shares = shares + ? WHERE user_id = ? AND quote_symbol = ?; ", number, session["user_id"], quote_symbol)

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?;", total_price, session["user_id"])
        # record the history of the operation
        user_id = session["user_id"]
        operation = "bought"
        today = date.today()
        db.execute("INSERT INTO history VALUES (?,?,?,?,?)", user_id, operation, quote_symbol, number, today)

        flash ("Purchased successfully")

        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/wallet", methods=["GET", "POST"])
@login_required
def wallet():
    """Show history of transactions"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?; ", session["user_id"])

    if request.method == "POST":

        try:
            number = float(request.form.get("number"))
        except ValueError:
             return apology("invalid input")

        if number <= 0 or not number:
            return apology("invalid input")
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?; ", number, session["user_id"])

    return render_template("wallet.html", cash = cash)

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    records = db.execute("SELECT * FROM history WHERE user_id = ?", session['user_id'])
    return render_template("history.html", records = records)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?;", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect(url_for("index"))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect(url_for('login'))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quotes = lookup(request.form.get("symbol"))
        # print(quotes)
        if not quotes:
            return apology("This quote is not exist!")

        return render_template("quote.html", quotes = quotes)

    return render_template("quote.html")






@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "POST":

        username = request.form.get("username")
        check_pass = request.form.get("password")

        if not check_pass:
            return apology("password is empty or space")

        if not username:
            return apology("username is empty or space")

        if check_pass != request.form.get("confirmation"):
            return apology("The conformation password is not matched")

        rows = db.execute("SELECT * FROM users WHERE username = ?;", username)

        if len(rows) != 0:
            return apology(f"The username '{username}' already exists. Please choose another name.")
        else:
            password = generate_password_hash(request.form.get("password"))
            db.execute("INSERT INTO users(username, hash) VALUES(? ,?);", username, password)
            return render_template("successful.html", placeholder = "Registration")
    else:
        return  render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    quote_symbol = request.form.get("symbol")
    number = request.form.get("shares")
    symbols = db.execute("SELECT * FROM quotes WHERE user_id = ?;", session["user_id"])

    if request.method == "POST":
        owned_shares = db.execute("SELECT * FROM quotes WHERE user_id = ? AND quote_symbol = ?;", session["user_id"], quote_symbol)
        number_have = int(owned_shares[0]["shares"])

        try:
            number = float(number)
            number = int(number)
        except ValueError:
             return apology("INVALID SHARES")

        if number <= 0:
            return apology ("the number of quotes must be at least 1")

        if number_have < number:
            return apology("You do not have this number of quotes!")

        quote_price = lookup(quote_symbol)["price"] * number
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?;", quote_price, session["user_id"])

        if number_have > number:
            db.execute("UPDATE quotes SET shares = shares - ? WHERE user_id = ?; ", number, session["user_id"])

        elif number_have == number:
            db.execute("DELETE FROM quotes WHERE quote_symbol = ? AND user_id = ?; ", quote_symbol, session["user_id"])

        else:
            return apology("You do not have this quote at all")

        # record the operation in the history
        user_id = session["user_id"]
        operation = "sell"
        today = date.today()
        db.execute("INSERT INTO history VALUES (?,?,?,?,?);", user_id, operation, quote_symbol, number, today)

        flash("Sold successfully")
        return redirect("/")



    return  render_template("sell.html", symbols = symbols)

