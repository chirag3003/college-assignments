CREATE DATABASE ass5;
USE ass5;


-- Create the Project table
CREATE TABLE Project (
    project_id VARCHAR(255) PRIMARY KEY, -- Assuming project_id can be strings like C353
    proj_name VARCHAR(255) NOT NULL,
    chief_arch VARCHAR(255)
);

-- Create the Employee table
CREATE TABLE Employee (
    Emp_id INT PRIMARY KEY,
    Emp_name VARCHAR(255) NOT NULL
);

-- Create the Assigned_To table (linking Project and Employee)
CREATE TABLE Assigned_To (
    Project_id VARCHAR(255),
    Emp_id INT,
    FOREIGN KEY (Project_id) REFERENCES Project(project_id),
    FOREIGN KEY (Emp_id) REFERENCES Employee(Emp_id)
);

-- Example insertions (replace with your actual data)
INSERT INTO Project (project_id, proj_name, chief_arch) VALUES
('C353', 'Project Alpha', 'Smith'),
('C354', 'Project Beta', 'Jones'),
('C453', 'Project Gamma', 'Williams'),
('Database', 'Database', 'Brown'),
('DBMS', 'DBMS', 'Davis');

INSERT INTO Employee (Emp_id, Emp_name) VALUES
(101, 'Alice'),
(102, 'Bob'),
(103, 'Charlie'),
(104, 'David'),
(105, 'Sarah');

INSERT INTO Assigned_To (Project_id, Emp_id) VALUES
('C353', 101),
('C353', 102),
('C354', 102),
('C354', 103),
('Database', 104),
('Database', 105),

-- Get the details of employees working on project C353
SELECT * FROM Employee WHERE Emp_id IN (
    SELECT Emp_id FROM Assigned_To WHERE Project_id = 'C353'
);

-- Get employee number of employees working on project C353
SELECT COUNT(*) FROM Assigned_To WHERE Project_id = 'C353';

--Obtain details of employees working on Database project
SELECT * FROM Employee WHERE Emp_id IN (
    SELECT Emp_id FROM Assigned_To WHERE Project_id = (SELECT project_id FROM Project WHERE proj_name = 'Database')
);

-- Get the details of all employees working on project C353 adn C354
SELECT *
FROM Employee
WHERE Emp_id IN (
    SELECT Emp_id
    FROM Assigned_To
    WHERE Project_id = 'C353'
)
AND Emp_id IN (
    SELECT Emp_id
    FROM Assigned_To
    WHERE Project_id = 'C354'
);
-- Get employee numbers of employees who do not work on project C453
SELECT COUNT(*) FROM Assigned_To WHERE Project_id != 'C453';

-- Get details of employees whose name starts with 'S'
SELECT * FROM Employee WHERE Emp_name LIKE 'S%';

-- Get details of all projects whose chief arch is smith
SELECT * FROM Project WHERE chief_arch = 'Smith';

-- Delete all project whose name is "DBMS"
DELETE FROM Project WHERE proj_name = 'DBMS';

-- Get project_id of Emp_id 101.
SELECT project_id FROM Assigned_To WHERE Emp_id = 101;


