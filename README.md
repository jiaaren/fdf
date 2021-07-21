### **Steps to execute program**
Tested for window users with WSL2 
1. Launch XLaunch
2. Display settings

		Multiple windows
		Display number: 0

3. Select how to start Xming

		Start no client

4. Specify parameter settings

		Tick: No Access Control

5. Finish
   
6. Run the following in command line in your WSL to save IP address to 'DISPLAY' environment variable
   - WSL2

			export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0

   - WSL1

			export DISPLAY=localhost:0.0 (WSL1)

### **Program overview/flowchart**
<img src="./references/fdf_flowchart.jpg">