# Parallelized Evolutionary Programming

This project is a paralelization of Evolutionary Programing, expecificly to find the minimun on the Ackley function.

## Author
Saúl Armas Gamiño
saul_armas@comunidad.unam.mx
## Afiliation
I'm student for the UNAM at the ENES on Morelia, Michoacan, México. 

![image](  https://drive.google.com/uc?export=view&id=1588bA0kcqUWbXuj-X9IGgq2HrPMvej3p)


## License
GNU General Public License v3.0

## How to install and run it
You need to have installed MPICH, you can follow the instructions [here.](https://www.mpich.org/static/downloads/3.3.2/mpich-3.3.2-installguide.pdf)
This project is for 1 computer, so install the gforker version.
When you had installed MPICH, follow the next steps: 
- Clone the repositorie.
- In a terminal,go to the path where is the folder "code" and open it.
- Run ```make clean  ``` and then ```make```
- Now, you would run ```mpiexec -n x ./ce ``` where x is the number of threads that you want the program use.
### note: 
To change the values of the variables, you need to open the code and declarate te value that you want, are in the fisrt lines belos the libraries, and to see changes, you have to do another ```make``` before do  ```mpiexec -n x ./ce ```

## Evolution Programimg
The Evolution Programimg was described as a form to simulate the evolution, "is one of a class of paradigms for simulating evolution which utilizes the concepts of Darwinian evolution to iteratively generate increasingly appropriate solutions (organisms) in light of a static or dynamically changing environment."Porto, V. W. (2018).

## Ackley function
"In mathematical optimization, the Ackley function is a non-convex function used as a performance test problem for optimization algorithms. It was proposed by David Ackley in his 1987 PhD Dissertation." [Wikipedia.](https://en.wikipedia.org/wiki/Ackley_function)

![image1](  https://drive.google.com/uc?export=view&id=1tHNd3P6C7yswbzeSQh2Kp9wtQ4F-XIpK)

## Methodology
We ask to the user the necesarie parameters, that are:
- <img src="https://render.githubusercontent.com/render/math?math=n">: represents the amount of variables that the solution would have.
- <img src="https://render.githubusercontent.com/render/math?math=\mu">: is the number of individuals that form the population.
- <img src="https://render.githubusercontent.com/render/math?math=G">: is the number of generations that the algoritm do each iteration.
- <img src="https://render.githubusercontent.com/render/math?math=\alpha">: is a mutation parameter.
- <img src="https://render.githubusercontent.com/render/math?math=\epsilon0">: the minor standard deviation allowed.
- <img src="https://render.githubusercontent.com/render/math?math=M">: the number of iterations for the algorithm.

Afther that, the algorithm do the next steps for each iteration:
- Get the initial solution that are the first fathers.
- Get the children from the fathers.
- Evaluate the population that is the union of the fathers and their children.
- Choose the best <img src="https://render.githubusercontent.com/render/math?math=\mu"> individuals, based on his score on the function, and these are going to be the fathers of the next generation, add 1 to the number of generations.
- When tha number of generations are equal to <img src="https://render.githubusercontent.com/render/math?math=G"> the best solution of the population is added to the list of best solutions

## Implementation
All the code is on C#, the used libraries on this work are:
- stdio.h
- stdlib.h
- math.h
- time.h
- mpi.h
- unistd.h



## Test
The test for this work was made whit the following parameters:
- <img src="https://render.githubusercontent.com/render/math?math=n = 5, 10"> and <img src="https://render.githubusercontent.com/render/math?math=15">
- <img src="https://render.githubusercontent.com/render/math?math=\mu = 100">
- <img src="https://render.githubusercontent.com/render/math?math=G = 200">
- <img src="https://render.githubusercontent.com/render/math?math=\alpha = 2">
- <img src="https://render.githubusercontent.com/render/math?math=\epsilon0 = 0.0001">
- <img src="https://render.githubusercontent.com/render/math?math=M = 15">
The goal is find the optimal point, that are the point which have the minimum value on f(x), and this is possible when all the n variables of the point are 0.
## Results
The results are on the folling table.

![image2](  https://drive.google.com/uc?export=view&id=1aKZeqMkHmEwd6-5rqrX_bGNtVaM8ZpaQ)

As we can see, it's more difficult to find the global optimal point when we use higher values for $n$, because are more variables that affect the value on f(x).
## Conclusions
Evolution programing can help you when you are finding for an optimal point on a function, on this work was used the Ackley function, but it can be whatever.

C# is a fast language of programming; it can be difficult but with practice you get used to it.

I think the results are good because the standard deviation is “lower” to my opinion, and it means that the algorithm is stable, and the best result that found isn’t so far to 0.

## Bibliography
Porto, V. W. (2018). Evolutionary programming. In Evolutionary Computation 1 (pp. 127-140). CRC Press.
Ackley, D. (2012). A connectionist machine for genetic hillclimbing (Vol. 28). Springer Science & Business Media.
MPICH. (n.d.). Web pages for MPI. Retrieved August 27, 2021, from https://www.mpich.org/static/docs/v3.3/



