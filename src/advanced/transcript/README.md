**Objective:** Trying lambdas in action and more practice with algorithms and 
iterators.

**Transcript** is a structure that holds the course records for a
  particular student. For each student there is a list of course/grade
  pairs for all the courses the student has passed. Again,
  **transcript.hpp** contains the description of the class that you will
  need to implement.

Implement first the functions **Add** and **RemoveById** that will add and 
remove entries from the registry. RemoveById should remove all entries with specific
student ID. This function is useful: **[remove_if](http://www.cplusplus.com/reference/algorithm/remove_if/)**.

Then implement functions **FindTranscript** and **FindCourseResults**:

- **FindTranscript** should find entries based on given student ID

- **FindCourseResults** should return a list of student ID and grade pairs
    corresponding to a course name.


**Compile and run:**
```bash
#In the folder src/advanced/transcript
make
cd src
./main
```