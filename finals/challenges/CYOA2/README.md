Choose Your Own Adventure 2
---------

A misc challenge about convert ints into floats, numerical and physical constants.

# Question Text
```
As you float into interstellar space, you cast your gaze onto the pointers of your
instrument...

Non-standard flag format: `[0-9]+`

nc ctf.pwn.sg 11006
```

*Creator -  prokarius (@prokarius)*

# Setup Guide

0. Install docker on the hosting system
1. Build the docker image with: `sh dockerbuild.sh`
2. Replace the port 11006 with your desired port in dockerrun.sh
3. Start the docker image: `sh dockerrun.sh`
4. Test the connectivity with netcat.

# Solution Details
Convert each integer number into the respective floating point number and
determine the letter of the constant that matches. Final hint spells

PLANCKS BAR

Suggesting to us that we are supposed to get the value of planck's constant hbar.
However, keeping to the theme of the problem, we will need to convert the float
into an integer. Get the most accurate value which is: 1.054571800E-34, and
convert it into an integer for the final value of:

118238520

### Solution table

| Given `int`  |  Converted `float`  |    Name of constant     | Letter |
|--------------|---------------------|-------------------------|--------|
| `1068077148` |  `1.324717957`      | Plastic Number          |   `P`  |
| `1805536572` |  `3.8275e26`        | Solar Luminosity        |   `L`  |
| `1005526689` |  `0.0072973525664`  | Fine Structure Constant |   `a`  |
| `1727990831` |  `6.02214086e23`    | Avogadro                |   `N`  |
| `1301214146` |  `299792458`        | Speed of Light          |   `c`  |
| `428181300`  |  `1.38064852e-23`   | Boltzmann Constant      |   `k`  |
| `1107313295` |  `32.065`           | Mass of Sulfur          |   `S`  |
| `0`          |  `0`                | Nothing                 |   ` `  |
| `993912976`  |  `2.8977729e-3`     | Wein's constant         |   `b`  |
| `778615823`  |  `5.2917721067e-11` | Bohr Radius             |   `a`  |
| `1090848777` |  `8.314462175`      | Ideal Gas constant      |   `R`  |

