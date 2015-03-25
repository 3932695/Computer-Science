/* IS325 HWK #7 - SQL PROGRAMMING - CHAPTER 5 */

/* Question 1.d */
UPDATE criminals SET mail_flag = 'Y';

/* Question 1.f */
UPDATE criminals SET phone = '7675659032' WHERE criminal_id = 1016;

/* Question 1.g */
DELETE FROM criminals WHERE criminal_id = 1017;

/* Question 2a. */
INSERT INTO crimes
	(crime_id, criminal_id, classification, date_charged, status)
	VALUES(100, 1010, 'M', '15-JUL-2005', 'PD');