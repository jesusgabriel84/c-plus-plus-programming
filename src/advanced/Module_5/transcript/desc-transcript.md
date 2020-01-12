**Objective:** Trying lambdas in action and more practice with algorithms and 
iterators and trying.

**Transcript** is a structure that holds the course records for a
  particular student. For each student there is a list of course/grade
  pairs for all the courses the student has passed. Again,
  **transcript.hpp** contains the description of the class that you will
  need to implement.

Implement first the functions **Add** and **RemoveById** that will add and 
remove entries from the registry. RemoveById should remove all entries with specific
student ID. Hint: **[remove_if](http://www.cplusplus.com/reference/algorithm/remove_if/)**.

Then implement functions **FindTranscript** and **FindCourseResults**:

- **FindTranscript** should find entries based on given student ID

- **FindCourseResults** should return a list of student ID and grade pairs
    corresponding to a course name.

These functions will not require many lines of code if you use
algorithms efficiently.