set pagesize 500

DROP TABLE Customers PURGE;
DROP TABLE Orders    PURGE;

CREATE TABLE Customers
(Customer#  NUMBER(4) ,
 LastName   VARCHAR2(10),
 FirstName  VARCHAR2(10));

INSERT INTO Customers VALUES(001,'Smith','Bob');
INSERT INTO Customers VALUES(002,'Lack','Sue');
INSERT INTO Customers VALUES(003,'Bundy','Kim');
INSERT INTO Customers VALUES(004,'Jones','Harry');
INSERT INTO Customers VALUES(005,'Jane','Susan');
commit;

CREATE TABLE Orders
(Customer#     NUMBER(4) ,
 Description   VARCHAR2(10),
 Quantity      Number(4));

INSERT INTO Orders VALUES(001,'Books',5);
INSERT INTO Orders VALUES(001,'Pens',10);
INSERT INTO Orders VALUES(002,'Erasers',5);
INSERT INTO Orders VALUES(004,'Jello',8);
commit;

column Description format a11

SELECT * FROM Customers;
SELECT * FROM Orders;


/* 5-7 - Cartesian Joins */

SELECT LastName, Description
  FROM Customers,
       Orders
  ORDER BY LastName, Description;

-- If you wanted to generate a template to be used for inventory

SELECT LastName, Description , '     ' Count
  FROM Customers  CROSS Join Orders
  ORDER BY LastName, Description;


/* 8-12 Equality JOINS */

SELECT * FROM Customers;
SELECT * FROM Orders;

SELECT Customers.Customer#,LastName, Description, Quantity
  FROM Customers,
       Orders
  WHERE Customers.Customer# = Orders.Customer#;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#;


SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#
   AND  c.Customer# IN (1, 4);


SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#
   AND  c.Customer# IN (1, 4)
  ORDER BY c.LastName;

SELECT c.Customer#, c.LastName LName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#
   AND  c.Customer# IN (1, 4)
  ORDER BY LName;


/* 13-14 Natural JOIN */

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c NATURAL JOIN Orders o;

SELECT Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c NATURAL JOIN Orders o;

/* 15 JOIN Using */

SELECT Customer#, LastName, Description, Quantity
  FROM Customers JOIN Orders
  USING (Customer#);

-- ORA-01748: only simple column names allowed 
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c JOIN Orders o
  USING (C.Customer#);

-- ORA-25154: column part of USING clause cannot have qualifier
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c JOIN Orders o
  USING (Customer#);

-- Valid
SELECT Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c JOIN Orders o
  USING (Customer#);

/* 16 JOIN ON */

DROP TABLE Orders2 purge;

CREATE TABLE Orders2
(CustNo     NUMBER(4) ,
 Description   VARCHAR2(10),
 Quantity      Number(4));

INSERT INTO Orders2 VALUES(001,'Books',5);
INSERT INTO Orders2 VALUES(001,'Pens',10);
INSERT INTO Orders2 VALUES(002,'Erasers',5);
INSERT INTO Orders2 VALUES(004,'Jello',8);
commit;

SELECT * FROM Orders2;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c JOIN Orders2 o
  ON  c.Customer# = o.CustNo;


/* 19-20 Non-Equality Joins - WHERE */

DROP TABLE promotion PURGE;
DROP TABLE books     PURGE;

create table promotion 
(gift  varchar2(15), 
minretail number(5,2), 
maxretail number(5,2)); 

Create table Books 
(ISBN VARCHAR2(10), 
Title VARCHAR2(30), 
PubDate DATE, 
PubID NUMBER (2), 
Cost NUMBER (5,2), 
Retail NUMBER (5,2), 
Category VARCHAR2(12),
  CONSTRAINT books_isbn_pk PRIMARY KEY(isbn)); 
 
insert into promotion  values ('BOOKMARKER', 0, 12); 
insert into promotion  values ('BOOK LABELS', 12.01, 25); 
insert into promotion  values ('BOOK COVER', 25.01, 56); 
insert into promotion  values ('FREE SHIPPING', 56.01, 999.99); 
Commit; 
 
INSERT INTO BOOKS 
VALUES ('1059831198','BODYBUILD IN 10 MINUTES A DAY','21-JAN-01',4,18.75,30.95, 'FITNESS'); 
INSERT INTO BOOKS 
VALUES ('0401140733','REVENGE OF MICKEY','14-DEC-01',1,14.20,22.00, 'FAMILY LIFE'); 
INSERT INTO BOOKS 
VALUES ('4981341710','BUILDING A CAR WITH TOOTHPICKS','18-MAR-05',2,37.80,59.95, 'CHILDREN'); 
INSERT INTO BOOKS 
VALUES ('8843172113','DATABASE IMPLEMENTATION','04-JUN-05',3,31.40,55.95, 'COMPUTER'); 
INSERT INTO BOOKS 
VALUES ('3437212490','COOKING WITH MUSHROOMS','28-FEB-06',4,12.50,19.95, 'COOKING'); 
INSERT INTO BOOKS 
VALUES ('3957136468','HOLY GRAIL OF ORACLE','31-DEC-05',3,47.25,75.95, 'COMPUTER'); 
INSERT INTO BOOKS 
VALUES ('1915762492','HANDCRANKED COMPUTERS','21-JAN-05',3,21.80,25.00, 'COMPUTER'); 
INSERT INTO BOOKS 
VALUES ('9959789321','E-BUSINESS THE EASY WAY','01-MAR-04',2,37.90,54.50, 'COMPUTER'); 
INSERT INTO BOOKS 
VALUES ('2491748320','PAINLESS CHILD-REARING','17-JUL-00',5,48.00,89.95, 'FAMILY LIFE'); 
INSERT INTO BOOKS 
VALUES ('0299282519','THE WOK WAY TO COOK','11-SEP-00',4,19.00,28.75, 'COOKING'); 
INSERT INTO BOOKS 
VALUES ('8117949391','BIG BEAR AND LITTLE DOVE','08-NOV-04',5,5.32,8.95, 'CHILDREN'); 
INSERT INTO BOOKS 
VALUES ('0132149871','HOW TO GET FASTER PIZZA','11-NOV-02',4,17.85,29.95, 'SELF HELP'); 
INSERT INTO BOOKS 
VALUES ('9247381001','HOW TO MANAGE THE MANAGER','09-MAY-05',1,15.40,31.95, 'BUSINESS'); 
INSERT INTO BOOKS 
VALUES ('2147428890','SHORTEST POEMS','01-MAY-05',5,21.85,39.95, 'LITERATURE'); 
commit;

SELECT * FROM promotion;
SELECT title, retail from books order by retail, title;

column retail    format 999.99
column minretail format 999.99
column maxretail format 999.99
SELECT * FROM promotion;
SELECT title, retail from books order by retail, title;

SELECT title, gift
  FROM books, promotion
  WHERE retail BETWEEN minretail AND maxretail;

SELECT title, gift
  FROM books JOIN promotion
  ON retail BETWEEN minretail AND maxretail;


/* 21-24 Self JOIN */

DROP TABLE employee purge;

CREATE TABLE employee
 (emp_no   varchar2(5),
  emp_name varchar2(20),
  sup_no   varchar2(5));

INSERT INTO employee VALUES('001','John Smith','100');
INSERT INTO employee VALUES('002','Harry Doe','100');
INSERT INTO employee VALUES('003','Jane Doe','100');
INSERT INTO employee VALUES('100','Main Boss','200');
commit;

SELECT * FROM employee;

SELECT a.emp_no, a.emp_name, b.emp_name
  FROM employee a,
       employee b
  WHERE a.sup_no = b.emp_no
  ORDER BY a.emp_no;

SELECT a.emp_no, a.emp_name, b.emp_name
  FROM employee a JOIN employee b
    ON a.sup_no = b.emp_no
  ORDER BY a.emp_no;


/* 25-28 Outer JOIN */
INSERT INTO Orders VALUES(100,'Cake',2);
commit;
SELECT * FROM Customers;
SELECT * FROM Orders;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#
  ORDER BY c.Customer#;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c,
       Orders    o
  WHERE c.Customer# = o.Customer#(+)
  ORDER BY c.Customer#;


SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c LEFT OUTER JOIN  Orders o
   ON c.Customer# = o.Customer#
  ORDER BY c.Customer#;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c RIGHT OUTER JOIN  Orders o
   ON c.Customer# = o.Customer#
  ORDER BY c.Customer#;

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Customers c FULL JOIN  Orders o
   ON c.Customer# = o.Customer#
  ORDER BY c.Customer#;

/* 29-32 Set Operators */
DROP TABLE BookAuthor    PURGE;
DROP TABLE Customers     PURGE;
DROP TABLE Orders        PURGE;

Create table Customers
(Customer#  NUMBER(4),
LastName VARCHAR2(10),
FirstName VARCHAR2(10),
Address VARCHAR2(20),
City VARCHAR2(12),
State VARCHAR2(2),
Zip VARCHAR2(5),
Referred NUMBER(4),
Region CHAR(2),
  CONSTRAINT customers_customer#_pk PRIMARY KEY(customer#) );

INSERT INTO CUSTOMERS
VALUES (1001, 'MORALES', 'BONITA', 'P.O. BOX 651', 'EASTPOINT', 'FL', '32328', NULL, NULL);
INSERT INTO CUSTOMERS
VALUES (1002, 'THOMPSON', 'RYAN', 'P.O. BOX 9835', 'SANTA MONICA', 'CA', '90404', NULL, NULL);
INSERT INTO CUSTOMERS 
VALUES (1003, 'SMITH', 'LEILA', 'P.O. BOX 66', 'TALLAHASSEE', 'FL', '32306', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1004, 'PIERSON', 'THOMAS', '69821 SOUTH AVENUE', 'BOISE', 'ID', '83707', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1005, 'GIRARD', 'CINDY', 'P.O. BOX 851', 'SEATTLE', 'WA', '98115', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1006, 'CRUZ', 'MESHIA', '82 DIRT ROAD', 'ALBANY', 'NY', '12211', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1007, 'GIANA', 'TAMMY', '9153 MAIN STREET', 'AUSTIN', 'TX', '78710', 1003, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1008, 'JONES', 'KENNETH', 'P.O. BOX 137', 'CHEYENNE', 'WY', '82003', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1009, 'PEREZ', 'JORGE', 'P.O. BOX 8564', 'BURBANK', 'CA', '91510', 1003, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1010, 'LUCAS', 'JAKE', '114 EAST SAVANNAH', 'ATLANTA', 'GA', '30314', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1011, 'MCGOVERN', 'REESE', 'P.O. BOX 18', 'CHICAGO', 'IL', '60606', NULL, NULL);  
INSERT INTO CUSTOMERS 
VALUES (1012, 'MCKENZIE', 'WILLIAM', 'P.O. BOX 971', 'BOSTON', 'MA', '02110', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1013, 'NGUYEN', 'NICHOLAS', '357 WHITE EAGLE AVE.', 'CLERMONT', 'FL', '34711', 1006, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1014, 'LEE', 'JASMINE', 'P.O. BOX 2947', 'CODY', 'WY', '82414', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1015, 'SCHELL', 'STEVE', 'P.O. BOX 677', 'MIAMI', 'FL', '33111', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1016, 'DAUM', 'MICHELL', '9851231 LONG ROAD', 'BURBANK', 'CA', '91508', 1010, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1017, 'NELSON', 'BECCA', 'P.O. BOX 563', 'KALMAZOO', 'MI', '49006', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1018, 'MONTIASA', 'GREG', '1008 GRAND AVENUE', 'MACON', 'GA', '31206', NULL, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1019, 'SMITH', 'JENNIFER', 'P.O. BOX 1151', 'MORRISTOWN', 'NJ', '07962', 1003, NULL); 
INSERT INTO CUSTOMERS 
VALUES (1020, 'FALAH', 'KENNETH', 'P.O. BOX 335', 'TRENTON', 'NJ', '08607', NULL, NULL); 
commit;


Create Table Orders 
(Order# NUMBER(4), 
Customer# NUMBER(4), 
OrderDate DATE, 
ShipDate DATE, 
ShipStreet VARCHAR2(18), 
ShipCity VARCHAR2(15), 
ShipState VARCHAR2(2), 
ShipZip VARCHAR2(5),
  CONSTRAINT orders_order#_pk PRIMARY KEY(order#)); 
 
INSERT INTO ORDERS VALUES (1000,1005,'31-MAR-05','02-APR-05','1201 ORANGE AVE', 'SEATTLE', 'WA', '98114'); 
INSERT INTO ORDERS VALUES (1001,1010,'31-MAR-05','01-APR-05', '114 EAST SAVANNAH', 'ATLANTA', 'GA', '30314'); 
INSERT INTO ORDERS VALUES (1002,1011,'31-MAR-05','01-APR-05','58 TILA CIRCLE', 'CHICAGO', 'IL', '60605'); 
INSERT INTO ORDERS VALUES (1003,1001,'01-APR-05','01-APR-05','958 MAGNOLIA LANE', 'EASTPOINT', 'FL', '32328'); 
INSERT INTO ORDERS VALUES (1004,1020,'01-APR-05','05-APR-05','561 ROUNDABOUT WAY', 'TRENTON', 'NJ', '08601'); 
INSERT INTO ORDERS VALUES (1005,1018,'01-APR-05','02-APR-05', '1008 GRAND AVENUE', 'MACON', 'GA', '31206'); 
INSERT INTO ORDERS VALUES (1006,1003,'01-APR-05','02-APR-05','558A CAPITOL HWY.', 'TALLAHASSEE', 'FL', '32307'); 
INSERT INTO ORDERS VALUES (1007,1007,'02-APR-05','04-APR-05', '9153 MAIN STREET', 'AUSTIN', 'TX', '78710'); 
INSERT INTO ORDERS VALUES (1008,1004,'02-APR-05','03-APR-05', '69821 SOUTH AVENUE', 'BOISE', 'ID', '83707'); 
INSERT INTO ORDERS VALUES (1009,1005,'03-APR-05','05-APR-05','9 LIGHTENING RD.', 'SEATTLE', 'WA', '98110'); 
INSERT INTO ORDERS VALUES (1010,1019,'03-APR-05','04-APR-05','384 WRONG WAY HOME', 'MORRISTOWN', 'NJ', '07960'); 
INSERT INTO ORDERS VALUES (1011,1010,'03-APR-05','05-APR-05', '102 WEST LAFAYETTE', 'ATLANTA', 'GA', '30311'); 
INSERT INTO ORDERS VALUES (1012,1017,'03-APR-05',NULL,'1295 WINDY AVENUE', 'KALMAZOO', 'MI', '49002'); 
INSERT INTO ORDERS VALUES (1013,1014,'03-APR-05','04-APR-05','7618 MOUNTAIN RD.', 'CODY', 'WY', '82414'); 
INSERT INTO ORDERS VALUES (1014,1007,'04-APR-05','05-APR-05', '9153 MAIN STREET', 'AUSTIN', 'TX', '78710'); 
INSERT INTO ORDERS VALUES (1015,1020,'04-APR-05',NULL,'557 GLITTER ST.', 'TRENTON', 'NJ', '08606'); 
INSERT INTO ORDERS VALUES (1016,1003,'04-APR-05',NULL,'9901 SEMINOLE WAY', 'TALLAHASSEE', 'FL', '32307'); 
INSERT INTO ORDERS VALUES (1017,1015,'04-APR-05','05-APR-05','887 HOT ASPHALT ST', 'MIAMI', 'FL', '33112'); 
INSERT INTO ORDERS VALUES (1018,1001,'05-APR-05',NULL,'95812 HIGHWAY 98', 'EASTPOINT', 'FL', '32328'); 
INSERT INTO ORDERS VALUES (1019,1018,'05-APR-05',NULL, '1008 GRAND AVENUE', 'MACON', 'GA', '31206'); 
INSERT INTO ORDERS VALUES (1020,1008,'05-APR-05',NULL,'195 JAMISON LANE', 'CHEYENNE', 'WY', '82003');
commit;

CREATE TABLE BOOKAUTHOR 
(ISBN VARCHAR2(10), 
AUTHORid VARCHAR2(4)); 
 
INSERT INTO BOOKAUTHOR VALUES ('1059831198','S100'); 
INSERT INTO BOOKAUTHOR VALUES ('1059831198','P100'); 
INSERT INTO BOOKAUTHOR VALUES ('0401140733','J100'); 
INSERT INTO BOOKAUTHOR VALUES ('4981341710','K100'); 
INSERT INTO BOOKAUTHOR VALUES ('8843172113','P105'); 
INSERT INTO BOOKAUTHOR VALUES ('8843172113','A100'); 
INSERT INTO BOOKAUTHOR VALUES ('8843172113','A105'); 
INSERT INTO BOOKAUTHOR VALUES ('3437212490','B100'); 
INSERT INTO BOOKAUTHOR VALUES ('3957136468','A100'); 
INSERT INTO BOOKAUTHOR VALUES ('1915762492','W100'); 
INSERT INTO BOOKAUTHOR VALUES ('1915762492','W105'); 
INSERT INTO BOOKAUTHOR VALUES ('9959789321','J100'); 
INSERT INTO BOOKAUTHOR VALUES ('2491748320','R100'); 
INSERT INTO BOOKAUTHOR VALUES ('2491748320','F100'); 
INSERT INTO BOOKAUTHOR VALUES ('2491748320','B100'); 
INSERT INTO BOOKAUTHOR VALUES ('0299282519','S100'); 
INSERT INTO BOOKAUTHOR VALUES ('8117949391','R100'); 
INSERT INTO BOOKAUTHOR VALUES ('0132149871','S100'); 
INSERT INTO BOOKAUTHOR VALUES ('9247381001','W100'); 
INSERT INTO BOOKAUTHOR VALUES ('2147428890','W105'); 
commit;

-- ====================================
SELECT authorid
 FROM books JOIN bookauthor USING(isbn)
 WHERE category = 'FAMILY LIFE';

SELECT authorid
 FROM books JOIN bookauthor USING(isbn)
 WHERE category = 'CHILDREN';

-- ==

SELECT authorid
 FROM books JOIN bookauthor USING(isbn)
 WHERE category = 'FAMILY LIFE'
UNION
SELECT authorid
 FROM books JOIN bookauthor USING(isbn)
 WHERE category = 'CHILDREN';

-- ==

SELECT customer#  FROM customers ORDER BY customer#;
SELECT customer#  FROM orders    ORDER BY customer#;

SELECT customer#  FROM customers
INTERSECT
SELECT customer#  FROM orders
 ORDER BY customer#;

SELECT customer#  FROM customers
MINUS
SELECT customer#  FROM orders
 ORDER BY customer#;

SELECT customer#  FROM customers
UNION
SELECT customer#  FROM orders
 ORDER BY customer#;

SELECT customer#  FROM customers
UNION ALL
SELECT customer#  FROM orders
 ORDER BY customer#;
