**Objective:** Understanding the basic handling of list, and using input
stream as a source.

This exercise reads series of lines into a list container from input
stream, that can be the standard input, or for example a file. You
will need to implement the following functions:

  * **GetLines(is, list)** that will read lines from the given input
  stream *is*, and add each line to list *list*. You will find
  function
**[getline](https://en.cppreference.com/w/cpp/string/basic_string/getline)**
  useful for reading lines from the input stream. The function will
  read as long as the input stream is readable. See
**[istream](https://en.cppreference.com/w/cpp/io/basic_istream)**
  reference for ideas how to check the input stream state. **Note:** A
common problem is that program tries to add one more item to the list after
a newline character that is at the end of the file. This should not be
done.

  * **Print(list)** that will print each string in the list on a
  separate line to the standard output stream.

  * **SortAndUnique(list)** that will sort the list into alphabetical
  order and remove duplicate strings. See [list] reference for further
  information.

[list]: https://en.cppreference.com/w/cpp/container/list

**Compile and run:**
```bash
#In the folder src/containers/list
make
cd src
./main
```
