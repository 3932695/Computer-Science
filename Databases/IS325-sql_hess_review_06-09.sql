@C:\SUNY\drop_everything

@H:\IS-325\Oracle_11g_SQL\Hess\IS325-sql_hess_review_06-09-setup

SET PAGESIZE 500
column Description format a11
column retail      format 999.99
column minretail   format 999.99
column maxretail   format 999.99


/* Cartesian Joins */

SELECT LastName, Description
  FROM Cust,
       Orders
  ORDER BY LastName, Description;

SELECT LastName, Description
  FROM Cust  CROSS Join Orders
  ORDER BY LastName, Description;


/* Equality JOINS */

SELECT Cust.Customer#,LastName, Description, Quantity
  FROM Cust,
       Orders
  WHERE Cust.Customer# = Orders.Customer#;

/* Natural JOIN */

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust c,
       Orders    o
  WHERE c.Customer# = o.Customer#;

SELECT Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust c NATURAL JOIN Orders o;

/* JOIN Using */

SELECT Customer#, LastName, Description, Quantity
  FROM Cust JOIN Orders
  USING (Customer#);

/* JOIN ON */

SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust c JOIN Orders2 o
  ON  c.Customer# = o.CustNo;


/* Non-Equality Joins - WHERE */

SELECT title, gift
  FROM books, promotion
  WHERE retail BETWEEN minretail AND maxretail;

SELECT title, gift
  FROM books JOIN promotion
  ON retail BETWEEN minretail AND maxretail;


/* Self JOIN */

SELECT a.emp_no, a.emp_name, b.emp_name
  FROM employee a,
       employee b
  WHERE a.sup_no = b.emp_no
  ORDER BY a.emp_no;

SELECT a.emp_no, a.emp_name, b.emp_name
  FROM employee a JOIN employee b
    ON a.sup_no = b.emp_no
  ORDER BY a.emp_no;


/* Outer JOIN */
-- Normal non-outer join
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust      c,
       Orders    o
  WHERE c.Customer# = o.Customer#
  ORDER BY c.Customer#;

-- Outer Join using WHERE clause
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust      c,
       Orders    o
  WHERE c.Customer# = o.Customer#(+)
  ORDER BY c.Customer#;

-- LEFT OUTER JOIN
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust c LEFT OUTER JOIN  Orders o
   ON c.Customer# = o.Customer#
  ORDER BY c.Customer#;

-- RIGHT OUTER JOIN
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust c RIGHT OUTER JOIN  Orders o
   ON c.Customer# = o.Customer#
  ORDER BY c.Customer#;

-- FULL JOIN
SELECT c.Customer#, c.LastName, o.Description, o.Quantity
  FROM Cust c FULL JOIN  Orders o
   ON c.Customer# = o.Customer#
  ORDER BY c.Customer#;


/* Set Operators */

SELECT customer#  FROM customers ORDER BY customer#;
SELECT customer#  FROM orders3   ORDER BY customer#;


-- UNION
SELECT customer#  FROM customers
UNION
SELECT customer#  FROM orders3
 ORDER BY customer#;

-- UNION ALL
SELECT customer#  FROM customers
UNION ALL
SELECT customer#  FROM orders3
 ORDER BY customer#;

-- INTERSECT
SELECT customer#  FROM customers
INTERSECT
SELECT customer#  FROM orders3
 ORDER BY customer#;

-- MINUS
SELECT customer#  FROM customers
MINUS
SELECT customer#  FROM orders3
 ORDER BY customer#;
