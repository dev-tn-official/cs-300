# cs-300
DSA Analysis and Design

# Data Structures and Algorithms Portfolio Reflection

## Overview
In this course, I developed a course advising assistance program for the Computer Science department at 'ABCU'. The goal of the project was to design and implement a system that could load course data from a CSV file, store it in an appropriate data structure, and allow advisors to retrieve information efficiently. The application needed to:

- Load course data into a data structure.
- Print a sorted list of all Computer Science courses in alphanumeric order.
- Print detailed information about an individual course, including prerequeisites.

Over the course of this term, we were tasked with working on various weekly assignments and occasional milestone projects. The first project focused on analyzing the runtime and memory characteristics of different data structures such as vector,s hash tables and binary search trees. The second project implemented a working C++ program using the data structure I recommended based on that analysis.


---

## What Problem Was Being Solved?

The main problem at hand was determining how to store and retrieve structured data such as courses and prerequisites in an efficient manner, while meeting functional requirements such as sorted output and fast lookup. In addition to simply makingn the program work, students were asked to evaluate which data structure best balanced performance, memory usage, and maintainability. This required thinking beyond basic syntax and focusing on algorithmic efficiency and scalability.


---

## Approach and Importance of Data Structures


### Project One - Analsis Phase
The following data structures were evaluated:
- Vectors
- Hash Tables
- Binary Search Trees

The runtime complexity, or 'Big-O' for loading data, searching, and printing sorted output were analyzed. From there, I compared advantages and disadvantages of each structure in the context of the program’s requirements.


### Project Two - Implementation Phase
Based off of what was discovered during the analysis phase, my chosen method was a Binary Search Tree style structure using 'std::map' in the C++ language, which maintains keys in a sorted order automatically. This allowed for efficient looksup, automatic alphanumeric sorting and clean, and easily readble implementation. Understanding data structures was critical here, as it directly influenced both the efficiency and clarity of possible solutions. Instead of sorting repeatedly or performing linear searches unnecessarily, the chosen structure handled ordering and lookup efficiently by design.


### Roadblocks and How I Overcame Them
The main challenges encountered during my time during the projects included the following:

- Ensuring prerequisites referenced valid courses.
- Handling duplicate course numbers.
- Managing invalid user input in the menu.
- Understanding how file paths and working directories affect file loading in Visual studio.

These challenges were overcome by breaking logic into smaller functions such as parsing, validation and printing, adding defensive programming practices such as input validation and file open checks, testing edge cases such as invalid menu input, missing files and invalid course searches, and iteratively refining formatting an user interaction to improve clarity and usability. During each term at SNHU, no matter the programming language employed, I have found that debugging and structured testing were key parts of the learning process, and it was necessary for me to make mistakes and learn from them in order to acheive success.


---

## Growth in Software Deisgn and Development
My approach to software design has changed and expanded in a few key ways:

- Thinking more deliberately about alagorithmic efficiency before writing any pseudocode or actual code.
- Separating concerns by organizing logic into separate, clearly defined functions.
- Evaluating trade-offs before moving forward with work instead of defaulting to the first working solution.
- Focusing on writing code that is not just functional but also easily maintainable by others and more easily readable, along with including comments that make various functions of the program clear.
- Not taking shortcuts during development by putting everything in 'main()' as opposed to properly structuring the program like one would see in the real world.

These design choices help users focus on their primary task without unnecessary friction or distractions.

---

## Maintainability, Readability, and Adaptability

I made efforts to ensure the program was written in an understandable and maintainable fashion, that could adapt to changes made by others in the future. These included the following steps:

- Using meaningful function names.
- Writing descriptive comments.
- Validating input and handling errors appropriately.
- Designing the program so changes from others could be isolated an more manageable.

As a result, this code could be conisdered modular and easy to modify. For example, if the data storage structure neeed to e changed in the future, the separation of processes such as file parsing, data storage and user interaction would make refractoring easier to perform.

---

## Portfolio Artifacts

The items in this repository include:

- Project One, which is a runtime and memory analysis comparing vectors, hash tables and ibnary search tree data structures.
- Project Two, which is a working C++ implementation of the advising assistance program taht sorts and prints course data in alphanumeric order.
- This README file.

These two items help demonstrate what I learned over the last several weeks about data structures, the importance of algorithmic efficiency and practical software development in C++.
