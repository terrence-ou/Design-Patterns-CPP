# SOLID Principles

`SOLID` Principles is a mnemonic acronym for five design principles intended to make object-oriented designs more understandable, flexible, and maintainable[1]. The members of `SOLID` principles are:

- **Single-responsibility principle**: <br>
    "A module should be responsible to one, and only one, actor." It is important to keep a class focused on a single concern to make the class more robust [2]. <br>
    Code: [01_single_responsibility.cpp](https://github.com/terrence-ou/Design-Patterns-CPP/blob/main/SOLID/01_single_responsibility.cpp)
    <br>
- **Open-closed principle**: <br>
    "Software entities (class, modules, function, etc.) should be open for extension, but closed for modification." That is, such an entity can allow its behavior to be extended without modifying its source code [3].<br>
    Code: [02_open_close.cpp](https://github.com/terrence-ou/Design-Patterns-CPP/blob/main/SOLID/02_open_close.cpp)

- **Liskov substitution principle**: <br>
    "An object (such as a class) may be replaced by a sub-object (such as a class that extends the first class) without breaking the program." LSP helps in creating a system that is more maintainable and scalable, as developers can trust in the consistent behavior of objects, regardless of their specific types [4].<br>
    Code: [03_liskov_substitution.cpp](https://github.com/terrence-ou/Design-Patterns-CPP/blob/main/SOLID/03_liskov_substitution.cpp)


- Interface segregation principle
- Dependency inversion principle

### *Reference:*
[1] SOLID: https://en.wikipedia.org/wiki/SOLID <br>
[2] Single-responsibility principle: https://en.wikipedia.org/wiki/Single-responsibility_principle <br>
[3] Open-close principle: https://en.wikipedia.org/wiki/Open%E2%80%93closed_principle <br>
[4] Liskov substitution principle: https://en.wikipedia.org/wiki/Liskov_substitution_principle <br>
