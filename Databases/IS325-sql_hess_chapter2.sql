/* WARNING - this routine will drop ALL objects */
/*           owned by the account that runs it  */
/*                                              */

/* run the following several times until no objects remain */

SPOOL do_purge_objects.sql
SELECT 'drop '||object_type||' '||object_name||';'
  FROM user_objects
  ORDER BY object_type,object_name;
SPOOL off
@do_purge_objects.sql

PURGE RECYCLEBIN;


/* Check to see if any objects remain */
column object_name format a32
column object_type format a32

SELECT object_name,object_type
 FROM user_objects
 ORDER BY object_type, object_name;

/* **************************************************** */

@bookscript.sql

PURGE RECYCLEBIN;

/* **************************************************** */

-- Create text table
DROP TABLE student PURGE;

CREATE TABLE student
 (name        VARCHAR2(20),
  phone       VARCHAR2(20),
  city        VARCHAR2(20),
  state       CHAR(02),
  tuition     NUMBER(10),
  scholarship NUMBER(10))
;

DESCRIBE student

INSERT INTO student VALUES('Hess', '315-555-5555','Marcy',  'NY',10000,1000);
INSERT INTO student VALUES('Jones','315-555-6666','Utica',  'NY',20000,0);
INSERT INTO student VALUES('Smith','315-555-7777','Buffalo','NY',12000,2000);
INSERT INTO student VALUES('Jay',  '315-555-8888','Tampa',  'FL',15000,7500);
commit;


set linesize 100
set pagesize 100

-- Basic SELECT statement

SELECT *
  FROM student;


SELECT name
  FROM student;

SELECT name, city
  FROM student;

-- Alias

SELECT name "Name of Student"
  FROM student;

-- Arithmetic Operation

SELECT tuition, scholarship, tuition-scholarship
  FROM student;

SELECT tuition, scholarship, tuition-scholarship "Student Bill"
  FROM student;

-- NULL

INSERT INTO student VALUES('Barns',  '315-555-9999','Mytown',  'FL',55000,'');
COMMIT:

SELECT tuition, scholarship, tuition-scholarship "Student Bill"
  FROM student;

-- Distinct

SELECT DISTINCT state
  FROM student;

SELECT UNIQUE state
  FROM student;

-- Concatentation

SELECT name, city||', '||state
  FROM student;

-- Line Break

SELECT name||CHR(10)||city||', '||state
  FROM student;









