CREATE DATABASE COMPANY;
USE COMPANY;

CREATE TABLE DEPT (
    DEPTNO INT PRIMARY KEY,
    DNAME VARCHAR(255) NOT NULL,
    LOC VARCHAR(255)
);

CREATE TABLE EMP (
    EMPNO INT PRIMARY KEY,
    ENAME VARCHAR(255) NOT NULL,
    JOB CHAR(20),  
    MGR INT,
    HIREDATE DATE,
    SAL DECIMAL(10, 2),
    COMM DECIMAL(10, 2), 
    DEPTNO INT,
    FOREIGN KEY (DEPTNO) REFERENCES DEPT(DEPTNO),
    FOREIGN KEY (MGR) REFERENCES EMP(EMPNO) 
);


-- Example insertions (optional, but highly recommended for testing)
INSERT INTO DEPT (DEPTNO, DNAME, LOC) VALUES
(10, 'ACCOUNTING', 'NEW YORK'),
(20, 'RESEARCH', 'DALLAS'),
(30, 'SALES', 'CHICAGO'),
(40, 'OPERATIONS', 'BOSTON');

INSERT INTO EMP (EMPNO, ENAME, JOB, MGR, HIREDATE, SAL, COMM, DEPTNO) VALUES
(7839, 'KING', 'PRESIDENT', NULL, '1981-11-17', 5000.00, NULL, 10),

-- 1. Display the unique designations for the employees:
SELECT DISTINCT JOB
FROM EMP;

-- 2. Delete Employees who joined in Year 1980:
DELETE FROM EMP
WHERE YEAR(HIREDATE) = 1980;

-- 3. Increase the salary of Managers by 20% of their current salary:
UPDATE EMP
SET SAL = SAL * 1.20  -- Increase by 20%
WHERE JOB = 'MANAGER';

-- 4. List employees not belonging to department 30, 40, or 10:
SELECT *
FROM EMP
WHERE DEPTNO NOT IN (30, 40, 10);

-- 5. List the different designations in the company (same as #1):
SELECT DISTINCT JOB
FROM EMP;

-- 6. List the names of employees who are not eligible for commission:
SELECT ENAME
FROM EMP
WHERE COMM IS NULL OR COMM = 0; -- Assuming 0 commission also means not eligible

-- 7. List employees whose names either start or end with “S”:
SELECT ENAME
FROM EMP
WHERE ENAME LIKE 'S%' OR ENAME LIKE '%S';

-- 8. List employees whose names have letter “A” as second letter in their names:
SELECT ENAME
FROM EMP
WHERE ENAME LIKE '_A%';

-- 9. List the number of employees working with the company:
SELECT COUNT(*) AS NumberOfEmployees
FROM EMP;


-- 10. List the salesmen who get the commission within a range of 200 and 500 (inclusive):
SELECT *
FROM EMP
WHERE JOB = 'SALESMAN' AND COMM BETWEEN 200 AND 500;
