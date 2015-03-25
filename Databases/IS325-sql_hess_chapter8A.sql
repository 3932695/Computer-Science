set pagesize 500

DROP TABLE Customers PURGE;

CREATE TABLE Customers
(Customer#  NUMBER(4) ,
 LastName   VARCHAR2(10),
 FirstName  VARCHAR2(10));

INSERT INTO Customers VALUES(001,'Smith','Bob');
INSERT INTO Customers VALUES(007,'White','Kay');
INSERT INTO Customers VALUES(002,'Smith','Sue');
INSERT INTO Customers VALUES(003,'Smith','Kim');
INSERT INTO Customers VALUES(004,'Jones','Bob');
INSERT INTO Customers VALUES(006,'Doe','Joe');
INSERT INTO Customers VALUES(005,'Jane','Susan');
INSERT INTO Customers VALUES(008,'Jane',NULL);

commit;

SELECT * FROM Customers;

===================================================
--
--  WHERE
--

SELECT Customer#, LastName||FirstName Name
  FROM Customers
  WHERE LastName||FirstName LIKE 'S%';

SELECT LastName, FirstName
  FROM Customers
  WHERE Customer# = 1;

--
-- BETWEEN
-- 
-- Select Customers who's Customer# >= 3 and <= 5

SELECT * FROM Customers
  WHERE Customer# >= 3
   AND  Customer# <= 5;


SELECT * FROM Customers
  WHERE Customer# BETWEEN 3 AND 5;



-- Select Customers who's Customer# < 3 and > 5

SELECT * FROM Customers
  WHERE Customer# NOT BETWEEN 3 AND 5;


-- Select Customers who's FirstName >= 'J' and <= 'S' 

SELECT * FROM Customers
  WHERE FirstName BETWEEN 'J' AND 'S';

SELECT * FROM Customers
  WHERE FirstName BETWEEN 'J' AND 'SZ';

SELECT * FROM Customers
  WHERE FirstName BETWEEN 'J' AND 'Sz';


-- Select Customers who's FirstName NOT >= 'J' and NOT <= 'S' 

SELECT * FROM Customers
  WHERE FirstName NOT BETWEEN 'J' AND 'Sz';


--
--  IN
--
--  Select Customers who's Customer# = 2 or 4 or 5

SELECT * FROM Customers
  WHERE Customer# = 2
   OR   Customer# = 4
   OR   Customer# = 5;


SELECT * FROM Customers
  WHERE Customer# IN (2, 4, 5);


--  Select Customers who's Customer# <> 2 and <> 4 and <> 5

SELECT * FROM Customers
  WHERE Customer# <> 2
   AND  Customer# <> 4
   AND  Customer# <> 5;


SELECT * FROM Customers
  WHERE Customer# NOT IN (2, 4, 5);


