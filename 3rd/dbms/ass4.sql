-- Create the database
CREATE DATABASE SupplierPartsProjects;
USE SupplierPartsProjects;

-- Create Suppliers table
CREATE TABLE Suppliers (
    Supplier_ID VARCHAR(5) PRIMARY KEY,
    Supplier_Name VARCHAR(255) NOT NULL,
    Supplier_Status INT,
    Supplier_City VARCHAR(255)
);

-- Create Parts table
CREATE TABLE Parts (
    Part_ID VARCHAR(5) PRIMARY KEY,
    Part_Name VARCHAR(255) NOT NULL,
    Part_Colour VARCHAR(255),
    Part_Weight DECIMAL(10, 2),
    Part_City VARCHAR(255)
);

-- Create Projects table
CREATE TABLE Projects (
    Project_ID VARCHAR(5) PRIMARY KEY,
    Project_Name VARCHAR(255) NOT NULL,
    Project_City VARCHAR(255)
);

-- Create Shipment table
CREATE TABLE Shipments (
    Supplier_ID VARCHAR(5),
    Part_ID VARCHAR(5),
    Project_ID VARCHAR(5),
    Quantity INT,
    FOREIGN KEY (Supplier_ID) REFERENCES Suppliers(Supplier_ID),
    FOREIGN KEY (Part_ID) REFERENCES Parts(Part_ID),
    FOREIGN KEY (Project_ID) REFERENCES Projects(Project_ID)
);

-- Sample Data Insertion (Optional but recommended for testing)
INSERT INTO Suppliers (Supplier_ID, Supplier_Name, Supplier_Status, Supplier_City) VALUES
('S1', 'Smith', 20, 'London'),
('S2', 'Jones', 10, 'Paris'),
('S3', 'Blake', 30, 'Paris'),
('S4', 'Clark', 20, 'London'),
('S5', 'Adams', 30, 'Athens');

INSERT INTO Parts (Part_ID, Part_Name, Part_Colour, Part_Weight, Part_City) VALUES
('P1', 'Nut', 'Red', 12.0, 'London'),
('P2', 'Bolt', 'Green', 17.0, 'Paris'),
('P3', 'Screw', 'Blue', 17.0, 'Rome'),
('P4', 'Screw', 'Red', 14.0, 'London'),
('P5', 'Cam', 'Blue', 12.0, 'Paris'),
('P6', 'Cog', 'Red', 19.0, 'London');

INSERT INTO Projects (Project_ID, Project_Name, Project_City) VALUES
('J1', 'Sorter', 'Paris'),
('J2', 'Display', 'Rome'),
('J3', 'OCR', 'Athens'),
('J4', 'Console', 'Athens'),
('J5', 'RAID', 'London'),
('J6', 'Sensor', 'London');

INSERT INTO Shipments (Supplier_ID, Part_ID, Project_ID, Quantity) VALUES
('S1', 'P1', 'J1', 200),
('S1', 'P1', 'J4', 700),
('S2', 'P3', 'J1', 400),
('S2', 'P3', 'J2', 200),
('S2', 'P3', 'J3', 200),
('S2', 'P3', 'J4', 500),
('S2', 'P3', 'J5', 600),
('S2', 'P3', 'J6', 400),
('S2', 'P5', 'J2', 100),
('S3', 'P3', 'J1', 200),
('S3', 'P4', 'J2', 500),
('S4', 'P6', 'J3', 300),
('S5', 'P2', 'J2', 100),
('S5', 'P2', 'J4', 200),
('S5', 'P5', 'J5', 500);

-- Queries:

-- 1. Get Supplier_ID for suppliers who supply project J1.
SELECT DISTINCT Supplier_ID
FROM Shipments
WHERE Project_ID = 'J1';

-- 2. Get Part_ID for parts supplied by a supplier in London.
SELECT DISTINCT Part_ID
FROM Shipments
WHERE Supplier_ID IN (SELECT Supplier_ID FROM Suppliers WHERE Supplier_City = 'London');

-- 3. Get the total quantity of part P1 supplied by S1.
SELECT SUM(Quantity)
FROM Shipments
WHERE Supplier_ID = 'S1' AND Part_ID = 'P1';

-- 4. Get project names for projects supplied by supplier S1.
SELECT DISTINCT Projects.Project_Name
FROM Projects
JOIN Shipments ON Projects.Project_ID = Shipments.Project_ID
WHERE Shipments.Supplier_ID = 'S1';

-- 5. Get colors of parts supplied by S1.
SELECT DISTINCT Parts.Part_Colour
FROM Parts
JOIN Shipments ON Parts.Part_ID = Shipments.Part_ID
WHERE Shipments.Supplier_ID = 'S1';

-- 6. Get all part-color/part-city combinations.
SELECT DISTINCT Part_Colour, Part_City
FROM Parts;

-- 7. Get Project_ID for projects supplied by at least one supplier.
SELECT DISTINCT Project_ID
FROM Shipments;

-- 8. Get colors of parts supplied by S1. (Same as 5)
SELECT DISTINCT Parts.Part_Colour
FROM Parts
JOIN Shipments ON Parts.Part_ID = Shipments.Part_ID
WHERE Shipments.Supplier_ID = 'S1';

-- 9. Delete all parts whose color is green.
DELETE FROM Parts
WHERE Part_Colour = 'Green';
