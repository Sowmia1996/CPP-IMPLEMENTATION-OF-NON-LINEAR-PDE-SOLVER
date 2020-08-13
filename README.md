# CPP-IMPLEMENTATION-OF-NON-LINEAR-SOLVER
This is a implementation of general-purpose non-linear 3-dimeansional partial-differential equations solver.<br>
In mathematics and physics, a nonlinear partial differential equation is a partial differential equation with nonlinear terms. 
They describe many different physical systems, ranging from gravitation to fluid dynamics, and have been used in mathematics to solve problems such as the Poincaré conjecture and the Calabi conjecture. 
The main challenge with solving non-linear pde is that they are difficult to study: there are almost no general techniques that work for all such equations, and usually each individual equation has to be studied as a separate problem.
<br><br>
Numerical solution on a computer is almost the only method that can be used for getting information about arbitrary systems of PDEs. There has been a lot of work done, but a lot of work still remains on solving certain systems numerically, especially for the Navier–Stokes and other equations related to weather prediction.
<br><br>
This repository is an implementation of non-linear pde solver based on finite-elements method<br>
In this method, functions are represented by their values at certain grid points and derivatives are approximated through differences in these values.

# Step:1 - derivatives for well-known analytical functions
we  write utility functions for calculating the exact derivatives of some well-known analytical functions<br><br>

# Step:2 - discretising the equation
We start by choosing uniformly-spaced grid-points in a particular region, and we approximate the given non-linear PDE's partial derivative terms of the function using the
central finite-difference scheme.
So now,solving the non-linear pde at these mesh-points boils down to solving a system of non-linear partial differntial equations<br>

# Step:3 - Solving the system of Non-Linear algebaraic equations
Newton method is a widely used iteration method in solving nonlinear algebraic equations. 
In this method, a linear algebraic equations need to be solved in every step. 
The coefficient matrix of the algebraic equations is so-called Jacobian matrix, which needs to be determined at every step. 
For a complex non-linear system, usually no explicit form of Jacobian matrix can be found.
After getting algebraic equations from a finite difference discretization, the Newton-Raphson method is applied to those non-linear algebraic equations.
This yields a square system of linear equations.If our mesh has dimension **mxn** then we would have to sovle a system of **nm non-linearal system** of algebraic equaions.

# Step:4-NEWTON'S METHOD:
We employ newton's for solving the system.But employing newton's method would requre us to calcualte the jacobian at each and every iteration.<br><br>
<img src="https://render.githubusercontent.com/render/math?math=X_{i+1}= X_i -\frac{f(x_i)}{f'(x_i)}">
<br>We know from Linear Algebra that we can take systems of equations and express those
systems in the form of matrices and vectors.Thus, the
following equation is derived:<br><br>
<img src="https://render.githubusercontent.com/render/math?math=X_{i+1}= X_i -(J(x_{i-1}))^{-1}F(x_i)">
<br><br>Where J is the jacobian matrix.This equation represents the procedure of Newton’s
method for solving nonlinear algebraic systems.
 #### NEWTON'S METHOD-STEP:1 - Start with a intial guess <img src="https://render.githubusercontent.com/render/math?math=X_0">
 #### NEWTON'S METHOD-STEP:2- Calculate J and F(x0) <br><br> 
#### NEWTON'S METHOD-STEP:3- Use newton's equation defined above to update the intial guess
#### NEWTON'S METHOD-STEP:3-Keep iterating until desired tolerance of convergence is achieved

This way we would be solving our non-linear system of equations<br><br>
But wait!!! Our matrix is going to be of size (mn*mn).What would happen if we chose a finer mesh?? the dimension of the jacobian matrix would blow up.Inverting 
such a huge matrix would be worser than the worst idea.<br><br>
**NEVER EVER INVERT A MATRIX THAT HUGE!!**

# TECHNIQUE FOR CALCULATING THE RHS OF HEWTON'S METHOD:
The point is,we never caluclate the inverse of matrices,we simply sovle for the equation<b>r><br>
 <img src="https://render.githubusercontent.com/render/math?math=J(x)y=F(x)"><br><br>
 Find a y and substitute in the newton's equation<br><br>
 
# Step:5- LINEAR SOLVER FOR INVERITNG JACOBIAN MATRIX
I implemented various linear solvers for solving the system of linear equations found in **linearslover.h**<br>
 - Guassian 
 - LU decomopstion
 - Tridiagonal matrix solver
 - Guass jacobian iterative method
 - Guass siedel iterative method
 - Successive over relaxation method
 
# THE CATCH:
In c++,we  have to store equations without actually evaluating them at any point inorder to avoid the agony of rewriting the eqaution for eacha and every grid-point.We want to to be general and not hard-code anything.To solve this problem,i 
- converted the deiscretised equation to its postfix-form (which is found in **postfixeval.h**
- And pushed them into a stack (which is found in **stackad.h**
- Whenever we need to evaluate the equation at  a grid-point,we simply pop from the stack until empty and evaluate
- a powerful use of data-structure!!!

# POSSIBLE INPROVISATIONS:
- We can deploy more advanced methods for solving the algebraic non-linear system of equations.
- The jacobian matrix is going to be a tridiagonal matrix.So instead of storing them as matrix,we can store the values in a compressed format<br>
 - compressed sparse row
 - compressed col
 - cordinate fomrat
 inorder to reduce space 


