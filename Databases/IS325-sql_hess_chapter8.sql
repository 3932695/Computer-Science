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

SELECT * FROM Customers
  WHERE Customer# = 001;

SELECT * FROM Customers
  WHERE Customer# > 001;

SELECT * FROM Customers
  WHERE Customer# >= 002;

SELECT * FROM Customers
  WHERE Customer# <> 001;


SELECT * FROM Customers
  WHERE Customer# BETWEEN 2 AND 100;


SELECT * FROM Customers
  WHERE LastName IN ('Smith');

SELECT * FROM Customers
  WHERE LastName IN ('Smith','Jones','AAA');


SELECT * FROM Customers
  WHERE FirstName LIKE 'S%';

SELECT * FROM Customers
  WHERE LastName LIKE 'J_ne';

SELECT * FROM Customers
  WHERE LastName LIKE 'J%';


SELECT * FROM Customers
  WHERE LastName  = 'Smith'
   AND  FirstName = 'Sue';

SELECT * FROM Customers
  WHERE LastName  = 'Smith'
   OR   FirstName = 'Kay';



SELECT * FROM Customers
  WHERE LastName  = 'Smith'
   AND  FirstName = 'Kim'
   OR   LastName  = 'Doe';

SELECT * FROM Customers
  WHERE LastName  = 'Smith'
   OR   LastName  = 'Doe'
   AND  FirstName = 'Kim';

SELECT * FROM Customers
  WHERE LastName  = 'Smith'
   OR   (LastName  = 'Doe'
    AND  FirstName = 'Kim');

SELECT * FROM Customers
  WHERE LastName  = 'Smith'
   AND  (FirstName = 'Kim'
     OR   LastName  = 'Doe');


SELECT * FROM Customers
  WHERE FirstName = NULL;

SELECT * FROM Customers
  WHERE FirstName IS NULL;


SELECT Customer#, LastName, FirstName
  FROM Customers;

SELECT Customer#, LastName, FirstName
  FROM Customers
  ORDER BY Customer#;

SELECT Customer#, LastName, FirstName
  FROM Customers
  ORDER BY 1;

SELECT Customer#, LastName, FirstName
  FROM Customers
  ORDER BY LastName, FirstName;

SELECT Customer#, LastName, FirstName
  FROM Customers
  ORDER BY LastName DESC, FirstName DESC;

SELECT Customer#, LastName, FirstName
  FROM Customers
  ORDER BY LastName DESC, FirstName;

SELECT Customer#, LastName, FirstName
  FROM Customers
  ORDER BY 2,3;





