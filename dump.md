Potential numerical integrators:
- Runge-Kutta
	- https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
	- Marginally more accurate than standard Euler methods
	- Testing over elongated periods of time may see artificial orbital decay
- Eulerian
	- https://en.wikipedia.org/wiki/Semi-implicit_Euler_method
	- The symplectic method in particular conserves energy much better than Runge-Kutta methods, while also being a more efficient means of calculation
	- It is the superior method for longer runtimes

- Fundamentals of Astrodynamics
- How do Wings Work?
- Non-Keplerian methods of optimising spacecraft trajectories (genuinely aids)
- Integrating Octave (FOSS alternative to Matlab) with our simulation to gather data at an industrial level 
- Research EBOs
	- Could optimise the drawing process for non-triangular shapes since GL works with triangles
	- Prevents having to draw vertexes in the same position multiple times
	- Attempt to draw a rectangle to test this