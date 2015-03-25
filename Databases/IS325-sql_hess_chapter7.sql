set pagesize 500

CREATE USER IS325_User
  IDENTIFIED BY Is325Pass;


SELECT * FROM 
  SYSTEM_PRIVILEGE_MAP;

DESCRIBE dba_sys_privs
DESCRIBE dba_role_privs

SELECT * FROM dba_sys_privs
  WHERE grantee = 'IS325_USER';

SELECT * FROM dba_role_privs
  WHERE grantee = 'IS325_USER';

GRANT create session to IS325_User;

SELECT * FROM dba_sys_privs
  WHERE grantee = 'IS325_USER';
SELECT * FROM dba_role_privs
  WHERE grantee = 'IS325_USER';

ALTER USER IS325_User
  IDENTIFIED BY Is325#1234;

SELECT * FROM dba_users
  WHERE username = 'IS325_USER';


drop user IS325_USER;

=====================================================


SELECT * from dba_sys_privs
  WHERE grantee = 'GAGNEP';

SELECT * from dba_role_privs
  WHERE grantee = 'GAGNEP';


SELECT distinct * from dba_sys_privs
  WHERE grantee IN ('CONNECT','RESOURCE')
  ORDER BY privilege;

SELECT distinct * from dba_role_privs
  WHERE grantee IN ('CONNECT','RESOURCE');

SELECT * from dba_tab_privs
  WHERE grantee = 'GAGNEP';



SELECT * from dba_tab_privs
  WHERE grantee = 'HESSR';
