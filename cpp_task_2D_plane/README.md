**Task Description:** Multi-threaded 2D Point Motion Tracking Interface

**Objective:**

- Create a multi-threaded program that allows users to define and manipulate points on a 2D plane. Users should be able to set new positions for the points, and the program should posts telemetry for each point's position during motion.
- Provide your solution as a git repository, please do not use public hosting services like github or gitlab. Instead, send back an archive with the git. Ensure that commit history reflects the progression of work on a real task.
- Provide docker configuration file for building and running

**Requirements:**

**User Input:**

- Allow the user to define the initial number of points on the 2D plane.
- Provide an interface for users to set new positions for each point dynamically.

**Telemetry:**

- Implement a mechanism to continuously update and display the current position of each point during motion.
- Telemetry should include both X and Y coordinates for each point.

**Communication Channel:**

- Implement a communication channel for user interaction and telemetry.

**Point Motion:**

- Allow users to request new positions for points while the program is executing motion for other points.
- Implement smooth and continuous motion updates for each point, (optionally user can set points "velocity")

**Note:**

- Use C++ and Python programming langiage.
- `PointManager`, `Point` skeletons are provided as reference; feel free to use as is or change.
- Points do not move if the user doesn't specify new position,
- Collisions during motion can be ignored,
- Assume Ubuntu 22.04 as the base system
- Feel free to ask clarification if needed.
