CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    head TEXT,
    PRIMARY KEY (id)
);

CREATE TABLE houses (
    studentId INTEGER,
    house TEXT
    FOREIGN KEY (studentId) REFERENCES students(id)

    );

CREATE TABLE heads(

    studentId INTEGER,
    head TEXT,
    FOREIGN KEY (studentId) REFERENCES students(id)

);


