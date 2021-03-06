Intel ® Rack Scale Architecture Reference Software – Getting Started guide 
 
NOTE ON PULL REQUESTS:
We are not upstreaming contributions to the master branch just yet. There are plans for this in the future. Once the process is established we will post information on this.

This ‘Getting Started’ guide is a good starting point for developers who are ready to start working with Intel ® Rack Scale Architecture Software. For details on Intel ® Rack Scale Architecture, please visit http://01.org/intelrackscalearchitecture or http://intel.com/intelrackscalearchitecture. It is recommended you read the entire document before getting started. Keep in mind this code is reference software only. It is expected developers will take this reference software and make it their own. Look for more releases in the future! Enjoy!

PLEASE READ: Documentation referenced in each of the steps below can be found on http://www.intel.com/content/www/us/en/architecture-and-technology/rack-scale-architecture/intel-rack-scale-architecture-resources.html.

1)	Have an understanding what hardware you'll be building on and what you have to work with and how Intel ® Rack Scale Architecture software will work with these components. See ‘Intel ® Rack Scale Architecture Hardware Platform Design Guide' for more detailed information.

2)	Read fully the 'Intel® Rack Scale Architecture PSME User Guide','Intel® Rack Scale Architecture Pod Manager User Guide' and 'Intel® Rack Scale Architecture RMM Software User Guide' documents (at link above). These documents are a great starting point for understanding the core components and how to set up your hardware and software components.

3)	Plan out how to configure your Intel ® Rack Scale Architecture software components across your hardware. You'll need to plan out which servers in your rack configurations will run which PSME and PODM components (also known as agents). 

Here is one example configuration (you don't have to do it this way)
•	Dedicate an Ubuntu 14.04 server with a BMC (e.g 1U on any rack) to run the PSME Compute and Core rest interface modules. For example, Dell PowerEdge, and HP ProLiant have this capability.
•	Dedicate a 10GbE TOR (or other) switch to run the PSME Core and Networking modules.
•	Dedicate another Storage server (disk controller) to run the PSME Core rest APIs and Storage agents/modules. This could potentially be the same dedicated server (with BMC) above for compute as the server could also have a storage controller and additional disks.  

4)	Download code you need from this GitHub repository.

5)	Read the 'PSME Rest API', 'PODM Rest API' and 'GAMI API' specifications as a reference and to understand how to work with the code.

6)	Build, install and modify the PSME components on your hardware configuration (see 'PSME User Guide'). You will need to modify the GAMI agents to interface with your hardware configuration.

7)	Build, install and modify the PODM components to talk with your PSME agents and manage your racks (see 'PODM User Guide').

8)	Connect to outside orchestration layer if you have one (e.g. OpenStack)

9)	Read the PSME and PODM 'release notes' to be aware of issues you may run into.

10)	Provide feedback by clicking the 'Issues' link in this GitHub repo. 

********************************************************DISCLAIMER*********************************************************

This code is reference software only and is not feature complete. It should not be used in commercial products at this time. Intel makes no claims for the quality or completeness of this code.
***************************************************************************************************************************
