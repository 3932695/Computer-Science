/* Guardians of the Cardinality Group Project
   Table creation
   Written by Claire Durgan
   This file contains the SQL statments that create the tables
   that are used for the representation of the data  */

/* if the tables exist for the data, drop the tables */

DROP TABLE College;
DROP TABLE Location;
DROP TABLE Student;
DROP TABLE Ethnicity;

/* Create the College table */
CREATE TABLE College (
 CollegeName VARCHAR2 (50),
 CollegeAcrage NUMBER (3),
 CollegeType  CHAR (2) DEFAULT 'PB',
 CollegeLocation VARCHAR2 (25),
 YearFounded NUMBER (4),
 FacultyStudentRatio VARCHAR2 (5));

/* Create the Student table */
CREATE TABLE Student (
 EnrollmentYear NUMBER (4),
 UndergradSize NUMBER (5),
 GraduateSize NUMBER (4),
 DoctoralSize NUMBER (4),
 AvgAge NUMBER (2,1),
 MFRatio NUMBER (2,1),
 CommuterPercentage VARCHAR2 (2),
 AvgSATScore VARCHAR2 (4),
 AvgACTScore VARCHAR2 (2));

/* Create Ethnicity Table */

CREATE TABLE Ethnicity (
 EnrollmentYear NUMBER (4),
 PercentWhite NUMBER (3,1),
 PercentAfricanAmerican NUMBER (3,1),
 PercentAsian NUMBER (3,1),
 PercentLatino NUMBER (3,1),
 PercentOther NUMBER (3,1));

/* Create the Location Table */
CREATE TABLE Location (
 CityName VARCHAR2(30),
 ZipCode VARCHAR2(5),
 State VARCHAR2(2),
 CityPopulation NUMBER (7),
 Description VARCHAR2 (255),
 CrimeRate NUMBER (4,2));

/* Create the faculty table */
CREATE TABLE Faculty (
 CollegeName VARCHAR2 (50),
 Department VARCHAR2 (25),
 DepartmentHead_LastName VARCHAR2 (25),
 DepartmentHead_FirstName VARCHAR2 (20),
 NumberTenured NUMBER (3),
 NumberAdjunct NUMBER (3));
 

/* If there are any more tables needed, feel free to let me know.
-Claire */
