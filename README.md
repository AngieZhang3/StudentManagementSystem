# StudentManagementSystem
 console app written in C++
 ## Introduction 
 A student management system written in C++ that meets the following requirements: 
-	Addition, deletion, modification and query of students, courses and grades
-	Processing large amounts of data: 100,000 students, 1,000 courses and 1million grade records. 
-	Query by ID, by name, allowing duplicate names (query time complexity: O(logn))
-	Cannot use third-party functions stl ( except cin, cout , fstream )
## Functions
### 2.1 Query
-	Query student name by student ID
-	Query student ID by student name
-	Query the course name by course ID
-	Query the course ID by course name
-	Query the students who have taken the course and their grades by course ID
-	Query the course information of the student by student ID
## 2.2 Insert
-	Add a new student (ID, name)
-	Add a new course (ID, name)
-	Add course selection record (student ID, course ID, score)
## 2.3 Delete
-	Delete student ( ID)
-	Delete course ( ID)
-	Delete course selection record ( student ID, course ID)
## 2.4 Update
-	Update student
-	Update course
-	Update course selection record
## Project Design
-	File Format and Data Storage
    - Input: Two text files - nameList.txt and CourseList.txt.
    - Output: Data stored in three binary files - ID_Name.bin, ID_Course.bin, and GradeList.bin.
-	Data Retrieval
    - Implement AVL trees to achieve efficient data retrieval.
-	Code Reuse and Flexibility
    - Use generic base classes and inheritance to enhance code reuse and flexibility.
