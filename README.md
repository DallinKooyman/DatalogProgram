# DatalogProgram
This project gets schemes, facts, rules, and queries from an input file and puts the information in a Datalog. Then it evaluates rules to add new facts. Finally, the code evaluates the queries by returning tuples that match the query. The project was made in 5 parts.
#### Part 1: The Lexer
The Lexer uses a finite state machine to read the input from the file and create tokens.
#### Part 2: Parser
The Parser takes the tokens from the lexer and parses them to determine correctness. The tokens must follow a strict order for the program to work.
#### Part 3: Interpreter
The Interpreter takes the information from the parser and creates relations. The relation is made up a header and a set of tuples to keep track of information. Once populated it evaluates the queries and returns tuples that match the question posed in the query.
#### Part 4: Evaluation of Rules
This part allows the implementation rules. The rules are evaluated by using a relational algebra operation. The relation on the right side and the join the relations on the right. Then project the columns from the left side and union the right relation with the left. This was done with a fixed point algorithm
#### Part 5: Speed Optimization
While all of the test cases I have run very quickly due to small sizes there is a faster way to accomplish the rule evaluation. The algorithm used can be found at:
```
https://people.eecs.berkeley.edu/~vazirani/algorithms/chap3.pdf
Section 3.4.2
```
The algorithm is roughly as follows:
Build a dependency graph for the rules. Create a reverse dependency Graph and do a Depth First Search Forest on the reverse graph. This gives us the post order for the reverse graph. If we then reverse that post order we get the correct order to search for the Strongly Connected Components (or strongly connected rules) in the original graph. We can then run a SCC evaluation. This will run the rules that aren't dependent on other rules or have a loop. A loop occurs when a rule relies on itself or relies on a different rule that relies on the original rule. This allows us to run rules less times. We evaluate rules in a SCC in order they appeared. Once a SCC is complete we can then move onto the next SCC. The code then finally outputs the Dependency graph, rule evaluation and query evaluation.


## Running Tests
Currently on the Part 5 tests can be run. However the code can be modified to run the other parts if you output the Lexer for part 1, DatalogProgram for part 2, remove the evaluate rules for part 3. Part 4 would be tricky currently.
In the future I may add support for each part. 

## Things I Learned
This was a really fun and challenging project for me. I learned about finite state machines, regular expression, grammars, more about logic and relations, relational data models, graph and graph dependencies. When I started I didn't even know what a regular expression was and then I built one. Evaluating queries was difficult because I had never projected, renamed, or selected from a relation data model. Now it feels second nature. Grab the tuples you need from the relation but not the others. Take only the columns you need. Now rename it so you can join the new info with the old in the relation. Evaluating rules to do the same was a little easier once I had done it. My favorite part was optimizing my code to run faster. Now I want to go back to old projects and see if I can apply this new knowledge to make them more efficient.

## Author
Dallin Kooyman  
Made in Visual Studio Community 2019 in the C++ language
