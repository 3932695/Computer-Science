-- QUESTION 1
-- Write a select statement that will retrieve the next number from sequence criminals_seq.  
-- You should use DUAL as the table in the select; e.g. SELECT xxx FROM DUAL;  You do not have to create the sequence.

SELECT criminals_seq.nextval FROM DUAL;

-- QUESTION 2
-- Write a DDL statement to change your Oracle account’s password to AB1234

ALTER USER xiaok
	IDENTIFIED BY AB1234;

-- QUESTION 3
-- Write a statement to create role General_user

CREATE ROLE General_user;

-- Write a statement to grant the role select on the criminals table

GRANT SELECT
	ON criminals
	TO General_user;
	
-- Write a statement to grant the role to your Oracle account

GRANT General_user
	TO xiaok;
	
-- QUESTION 4
-- Refer to CJ_08.sql

-- List all criminal aliases that begin with the letter B.

SELECT alias FROM aliases
	WHERE alias LIKE 'B%';
	
-- List all crimes that have a status of CA or IA. List the crime id, criminal id, date charged, and status.

SELECT crime_id, criminal_id, date_charged, status FROM crimes 
	WHERE status IN ('CA', 'IA');

-- List all criminals who have a zip code of 23510. List the criminal id, last name, and zip code. Sort the list by criminal id.

SELECT criminal_id, last, zip FROM criminals 
	WHERE zip IN('23510')
	ORDER BY criminal_id;

-- List all crimes that do not have a hearing date scheduled. List the crime id, criminal id, date charged, and hearing date. 

SELECT crime_id, criminal_id, date_charged, hearing_date FROM crimes 
	WHERE hearing_date IS NULL;

-- List all police officers who are assigned to either a precinct of OCVW or GHNT and have a status of active.  
-- List the officer id, last name, precinct, and status.  Sort the list by precinct then officer last name. 

SELECT officer_id, last, precinct, status FROM officers 
	WHERE precinct IN('OCVW', 'GHNT') 
	AND status = 'A' 
	ORDER BY precinct, last;

-- QUESTION 5
-- Refer to CJ_09.sql

-- Provide a list of all criminals along with crime information.  
-- The report needs to include the criminal id, name, crime classification, date charged, crime code, and fine amount.  
-- Include only crimes that are classified as "Other."  Sort the list by criminal id and date charged. 

SELECT criminals.criminal_id, last, first, classification, date_charged, crime_code, fine_amount FROM criminals, crimes, crime_charges 
	WHERE criminals.criminal_id = crimes.criminal_id 
	AND crimes.crime_id = crime_charges.crime_id;
	
SELECT criminal_id, last, first, classification, date_charged, crime_code, fine_amount FROM criminals 
	NATURAL JOIN crimes 
	NATURAL JOIN crime_charges;


-- Provide an alphabetical list of all criminals including criminal id, name, violent offender status, parole status, and any known aliases.

SELECT criminal_id, last, first, v_status, p_status, alias FROM criminals 
	NATURAL JOIN aliases
	ORDER BY last; -- assuming alphabetically by last name.
