SELECT 'drop '||object_type||' '||object_name||';' FROM user_objects;

PURGE recyclebin

===================================================================
-- Sequence - NOCYCLE

DROP SEQUENCE Customer_Sequence;

CREATE SEQUENCE Customer_Sequence
 INCREMENT by 1
 START WITH   1
 MAXVALUE     5
 MINVALUE     1
 NOCYCLE
 CACHE 3
;

SELECT * FROM user_sequences;

-- DO 6 times

SELECT Customer_Sequence.nextval FROM dual;

===================================================================
-- Sequence - CYCLE

DROP SEQUENCE Customer_Sequence;

CREATE SEQUENCE Customer_Sequence
 INCREMENT by 1
 START WITH   1
 MAXVALUE     5
 MINVALUE     1
 CYCLE
 CACHE 3
;

-- DO 6 times

SELECT Customer_Sequence.nextval FROM dual;

===================================================================
-- Sequence - nextval/currval

DROP SEQUENCE Customer_Sequence;

CREATE SEQUENCE Customer_Sequence
 INCREMENT by 100
 START WITH   900
;

SELECT Customer_Sequence.nextval FROM dual;

SELECT Customer_Sequence.currval FROM dual;

-- Try in another session

===================================================================
-- Sequence - Use for Customer#

DROP TABLE customers PURGE;

CREATE TABLE Customers
(Customer#  NUMBER(4)     constraint customer_pk PRIMARY KEY,
LastName    VARCHAR2(10),
FirstName   VARCHAR2(10),
Address     VARCHAR2(20),
City        VARCHAR2(12),
State       VARCHAR2(2),
Zip         VARCHAR2(5))
;

INSERT INTO customers
 (Customer#)
 VALUES (Customer_Sequence.nextval)
;

select * from Customers;
commit;

-- Note currval, last_number, and cache_size

SELECT Customer_Sequence.currval FROM dual;
SELECT * FROM user_sequences;

===================================================================
-- Sequence - alter

refer to page 167 - 168 of text


===================================================================
-- Indexes

DROP TABLE Customers PURGE;

CREATE TABLE Customers
(Customer#  NUMBER(4)     constraint customer_pk PRIMARY KEY,
LastName    VARCHAR2(10),
FirstName   VARCHAR2(10),
Address     VARCHAR2(20),
City        VARCHAR2(12),
State       VARCHAR2(2)   constraint customer_state_uk UNIQUE,
Zip         VARCHAR2(5))
;

-- Oracle creates an index for PK and UK

SELECT * FROM user_constraints
 WHERE table_name = 'CUSTOMERS';

SELECT * FROM user_indexes
 WHERE table_name = 'CUSTOMERS';

-- TABLE ALTER Example

DROP TABLE Customers PURGE;

CREATE TABLE Customers
(Customer#  NUMBER(4),
LastName    VARCHAR2(10),
FirstName   VARCHAR2(10),
Address     VARCHAR2(20),
City        VARCHAR2(12),
State       VARCHAR2(2),
Zip         VARCHAR2(5))
;

ALTER TABLE Customers
 ADD constraint customer_PK PRIMARY KEY (Customer#)
  USING INDEX;

CREATE INDEX Customer_zip_state_IE1 
  ON Customers(Zip, State);

CREATE UNIQUE INDEX Customer_City_AK1
  ON Customers(City);

SELECT * FROM user_constraints
 WHERE table_name = 'CUSTOMERS';

SELECT index_name, index_type, table_name, uniqueness
 FROM user_indexes
 WHERE table_name = 'CUSTOMERS';

column column_name format a32

SELECT index_name, column_name, column_position
  FROM user_ind_columns
  WHERE table_name = 'CUSTOMERS'
  ORDER by index_name,column_position;

-- Function Index
CREATE INDEX Customer_LastName_fn1 
  ON Customers UPPER(LastName);

===================================================================
-- Synonyms

INSERT INTO Customers (Customer#) VALUES(100);
commit;

SELECT * FROM Customers;


DROP SYNONYM mytable;

CREATE SYNONYM mytable
  FOR customers;

SELECT * FROM mytable;

SELECT * FROM user_synonyms;


