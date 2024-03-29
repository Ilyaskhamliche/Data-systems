SELECT e.EMP_FNAME, e.EMP_LNAME, j.JOB_DESCRIPTION
FROM EMPLOYEE e
JOIN JOB j ON e.JOB_CODE = j.JOB_CODE;

SELECT a.*
FROM ASSIGNMENT a
JOIN PROJECT p ON a.PROJECT_NUMBER = p.PROJ_NUM
WHERE p.PROJ_NAME = 'Starflight';

SELECT e.EMP_FNAME, e.EMP_LNAME, e.EMP_HIREDATE
FROM EMPLOYEE e
JOIN JOB j ON e.JOB_CODE = j.JOB_CODE
WHERE j.JOB_DESCRIPTION = 'DSS Analyst';

SELECT COUNT(*) AS num_project_managers
FROM PROJECT
WHERE JOB_CODE = 'PM';

SELECT e.EMP_FNAME, e.EMP_LNAME, SUM(a.CHARGE) AS total_assignment_charges
FROM EMPLOYEE e
JOIN ASSIGNMENT a ON e.EMP_NUM = a.EMP_NUM
GROUP BY e.EMP_FNAME, e.EMP_LNAME;

SELECT DISTINCT e.*
FROM EMPLOYEE e
JOIN ASSIGNMENT a ON e.EMP_NUM = a.EMP_NUM
JOIN JOB j ON e.JOB_CODE = j.JOB_CODE
JOIN PROJECT p ON a.PROJECT_NUMBER = p.PROJ_NUM
WHERE j.JOB_DESCRIPTION = 'Programmer' AND p.PROJ_NAME = 'Amber Wave';

SELECT DISTINCT e.*
FROM EMPLOYEE e
JOIN ASSIGNMENT a ON e.EMP_NUM = a.EMP_NUM
JOIN JOB j ON e.JOB_CODE = j.JOB_CODE
JOIN PROJECT p ON a.PROJECT_NUMBER = p.PROJ_NUM
WHERE j.JOB_DESCRIPTION = 'Programmer' AND p.PROJ_NAME = 'Amber Wave';
