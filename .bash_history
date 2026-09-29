sudo apt update
sudo apt install gcc -ysudo apt update
sudo apt install gcc -y
# Clone your repository (replace with your actual GitHub/GitLab URL)
git clone https://github.com/yourusername/your-repo-name.git
# Move into your repository folder
cd your-repo-name
# Configure Git so it allows you to commit (use your GitHub email and name)
git config --global user.email "your-email@example.com"
git config --global user.name "Your Name"
# Clone your repository (replace with your actual GitHub/GitLab URL)
git clone https://github.com/yourusername/your-repo-name.git
# Move into your repository folder
cd your-repo-name
# Configure Git so it allows you to commit (use your GitHub email and name)
git config --global user.email "your-email@example.com"
git config --global user.name "Your Name"miklr
git clone https://github.com/it24101497/PC-Lab-7.git
cd SE3082-2026-Sem02-Lab06
git clone https://github.com/it24101497/PC-Lab-7.git
cd PC-Lab-7
mkdir Exercise1
cd Exercise1
nano exercise1.c
gcc -fopenmp exercise1.c -o exercise1
./exercise1
sudo apt update
sudo apt install openmpi-bin libopenmpi-dev -y
gcc -fopenmp exercise1.c -o exercise1
./exercise1
nano exercise1.c
gcc -fopenmp exercise1.c -o exercise1
./exercise1
mpicc exercise1.c -o exercise1
mpirun -np 4 ./exercise1
mpirun --oversubscribe -np 4 ./exercise1
git add exercise1.c
git commit -m "Add Lab 7 MPI Exercise 1 code"
git push origin main
nano answers.txt
git add answers.txt
git commit -m "Add written answers for lab exercises"
git push origin main
cd PC-Lab-7
mkdir Exercise2
nano exercise2.c
mpicc exercise2.c -o exercise2
mpirun --oversubscribe -np 4 ./exercise2
cd PC-Lab-7
mkdir -p Exercise2
cd Exercise2
nano exercise2.c
mpicc exercise2.c -o exercise2
mpirun --oversubscribe -np 4 ./exercise2
git add exercise2.c
git commit -m "Add Lab 7 MPI Exercise 2 - Scatter"
git push origin main
cd ..
mkdir -p Exercise3
cd Exercise3
nano exercise3.c
mpicc exercise3.c -o exercise3
mpirun --oversubscribe -np 4 ./exercise3
git add exercise3.c
git commit -m "Add Lab 7 MPI Exercise 3 - Gather"
git push origin main
cd ~/PC-Lab-7
mkdir -p Exercise4
cd Exercise4
nano exercise4.c
mpicc exercise4.c -o exercise4
mpirun --oversubscribe -np 4 ./exercise4
git add exercise4.c
git commit -m "Add Lab 7 MPI Exercise 4 - Reduce"
git push origin main
cd ..
mkdir -p Exercise5
cd Exercise5
nano exercise5.c
mpicc exercise5.c -o exercise5
mpirun --oversubscribe -np 4 ./exercise5
git add exercise5.c
git commit -m "Add Lab 7 MPI Exercise 5 - Allreduce"
git push origin main
cd ..
mkdir -p Exercise6
cd Exercise6
nano exercise6.c
mpicc exercise6.c -o exercise6
mpirun --oversubscribe -np 4 ./exercise6
git add exercise6.c
git commit -m "Add Lab 7 MPI Exercise 6 - Scan"
git push origin main
git add exercise6.c
git commit -m "Add Lab 7 MPI Exercise 6 - Scan"
git push origin main
cd ~/PC-Lab-7
nano Makefile
make run
sudo apt update
sudo apt install make -y
make run
git add Makefile
git commit -m "Complete Exercise 8 - Add Makefile to run all programs"
git push origin main
mkdir Exercise7
cd ~/PC-Lab-7
mkdir Exercise7
touch Exercise7/.keep
git add Exercise7/
git commit -m "Create Exercise 7 folder"
git push origin main
