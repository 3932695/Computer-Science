set pagesize 100
set linesize 100
set long     100
COLUMN data_default     FORMAT a15
COLUMN search_condition FORMAT a28
COLUMN column_name      FORMAT a32

DROP TABLE Alias	 		PURGE;
DROP TABLE Criminals 		PURGE;
DROP TABLE Crimes			PURGE;
DROP TABLE Sentences 		PURGE;
DROP TABLE Prob_officers	PURGE;
DROP TABLE Crime_charges	PURGE;
DROP TABLE Crime_officers	PURGE;
DROP TABLE Officers			PURGE;
DROP TABLE Appeals			PURGE;
DROP TABLE Crime_codes		PURGE;

CREATE TABLE Alias (
	Alias_id 		NUMBER(6, 0),
	Criminal_id  	NUMBER(6, 0),
	Alias     		VARCHAR2(10)
);

CREATE TABLE Criminals (
	Criminal_ID  	NUMBER(6, 0),
	Last      	 	VARCHAR2(15),
	First     		VARCHAR2(10),
	Street     		VARCHAR2(30),
	City	     	VARCHAR2(20),
	State			CHAR(2),
	Zip				CHAR(5),
	Phone			CHAR(10),
	V_status		CHAR(1) DEFAULT 'N',
	P_status		CHAR(1) DEFAULT 'N'
);
  
CREATE TABLE Crimes (
	Crime_id		NUMBER(9, 0),
	Criminal_id		NUMBER(6, 0),
	Classification	CHAR(1),
	Date_charged	DATE,
	Status			CHAR(2),
	Hearing_date	DATE,
	Appeal_out_date	DATE
);

CREATE TABLE Sentences (
	Sentence_ID		NUMBER(6, 0),
	Criminal_ID		NUMBER(6, 0),
	Type			CHAR(1),
	Prob_id			NUMBER(5, 0),
	Start_date		DATE,
	End_date		DATE,
	Violations		NUMBER(3, 0)
);

CREATE TABLE Prob_officers (
	Prob_id 		NUMBER(5, 0),
	Last			VARCHAR2(15),
	First			VARCHAR2(10),
	Street     		VARCHAR2(30),
	City	     	VARCHAR2(20),
	State			CHAR(2),
	Zip				CHAR(5),
	Phone			CHAR(10),
	Email     		VARCHAR2(30),
	Status			CHAR(1)
);
	
CREATE TABLE Crime_charges (
	Charge_id		NUMBER(10, 0),
	Crime_id		NUMBER(9, 0),
	Crime_code		NUMBER(3, 0),
	Charge_status	CHAR(2),
	Fine_amount		NUMBER(7, 2),
	Court_fee		NUMBER(7, 2),
	Amount_paid		NUMBER(7, 2),
	Pay_due_date	DATE
);

CREATE TABLE Crime_officers (
	Crime_id		NUMBER(9, 0),
	Officer_id		NUMBER(8, 0)
);

CREATE TABLE Officers (
	Officer_id		NUMBER(8, 0),
	Last			VARCHAR2(15),
	First			VARCHAR2(10),
	Precinct		CHAR(4),
	Badge			VARCHAR2(14),
	Phone			CHAR(10),
	Status			CHAR(1) DEFAULT 'A'
);

CREATE TABLE Appeals(
	Appeal_id 		NUMBER(5, 0),
	Crime_id		NUMBER(9, 0),
	Filing_date		DATE,
	Hearing_date	DATE,
	Status			CHAR(1) DEFAULT 'P'
);

CREATE TABLE Crime_codes (
	Crime_code 			NUMBER(3, 0),
	Code_description	VARCHAR2(30)
);

ALTER TABLE Crimes
	MODIFY (Classification DEFAULT 'U');

ALTER TABLE Crimes
	ADD (Date_Recorded DATE DEFAULT SYSDATE);
	
ALTER TABLE Prob_officers
	ADD (Pager# NUMBER(10, 0));
	
ALTER TABLE Alias
	MODIFY (Alias VARCHAR2(20));