# revery-workbook

A minimal Workbook desktop client written in Revery

---
### Setup

You need to enter a valid `user` and `pass` in `Fetch.re`:

```reasonml
let user = "USER";
let pass = "PASS";
```

You also need to enter your workbook api base url in `Workbook.re`:

```reasonml
let baseUrl = "http://workbook.HOSTNAME.com/api";
```

---
### Installation

Using [esy](https://esy.sh/):

    $ esy install
    $ esy build

The binary will be in the `_build/install/default/bin` - you can run it like:

- `_build/install/default/bin/App`

or with esy:

- `esy run`

---
### Usage

1. Enter your name in the search field.
2. Press *Get*.
3. Enter an int or a float in one or more of the available fields.
4. Press *Post*.

---
### Credits

revery-workbook is built and maintained by **babangsund**.  
[@blog](https://babangsund.com/).  
[@github](https://github.com/babangsund).  
[@twitter](https://twitter.com/babangsund). 
