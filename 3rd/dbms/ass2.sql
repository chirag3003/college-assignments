-- Create the first database (e.g., 'project_management')
CREATE DATABASE project_management;
USE project_management;

CREATE TABLE Project (
    project_id INT PRIMARY KEY,
    proj_name VARCHAR(255) NOT NULL,
    chief_arch VARCHAR(255) NOT NULL  
);

CREATE TABLE Employee (
    Emp_id INT PRIMARY KEY,
    Emp_name VARCHAR(255) NOT NULL
);

CREATE TABLE Assigned_To (
    Project_id INT,
    Emp_id INT,
    FOREIGN KEY (Project_id) REFERENCES Project(project_id),
    FOREIGN KEY (Emp_id) REFERENCES Employee(Emp_id)
);


CREATE DATABASE work_scheduling;
USE work_scheduling;

CREATE TABLE Employee (
    emp_no INT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    skill VARCHAR(255) NOT NULL,
    pay_rate DECIMAL(10, 2) NOT NULL,
    CHECK (pay_rate >= 0)
);

CREATE TABLE Position (
    posting_no INT PRIMARY KEY,
    skill VARCHAR(255) NOT NULL
);

CREATE TABLE Duty_allocation (
    posting_no INT,
    emp_no INT,
    day DATE NOT NULL,
    shift VARCHAR(50) NOT NULL,
    FOREIGN KEY (posting_no) REFERENCES `Position`(posting_no), -- Then foreign keys
    FOREIGN KEY (emp_no) REFERENCES Employee(emp_no)
);


INSERT INTO Employee (emp_no, name, skill, pay_rate) VALUES
(1, 'John Doe', 'Programming', 50.00),
(2, 'Jane Smith', 'Database', 60.00);

INSERT INTO Position (posting_no, skill) VALUES
(101, 'Programming'),
(102, 'Database');

INSERT INTO Duty_allocation (posting_no, emp_no, day, shift) VALUES
(101, 1, '2024-10-27', 'Morning'),
(102, 2, '2024-10-27', 'Afternoon');


INSERT INTO Project (project_id, proj_name, chief_arch) VALUES
(1, 'Project Alpha', 'John Doe');

INSERT INTO Employee (Emp_id, Emp_name) VALUES
(10, 'John Doe'),
(11, 'Jane Smith');

INSERT INTO Assigned_To (Project_id, Emp_id) VALUES
(1, 10),
(1, 11);
