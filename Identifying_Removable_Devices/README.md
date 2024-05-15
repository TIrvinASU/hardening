Our team received a list of minimum devices that are required to be kept from our sponsor. This list was not exhaustive of all the devices that should be present in the final device tree, but offered a starting point to distinguish what devices are necessary and what aren't.

We started by identifying the devices that matched those in the list given to us. This was done by investigating the purpose of each device in the device tree (as we weren't familiar with a lot of the various hardware components beforehand), investigating the purpose of each device in the minimum list given to us, and matching those with the same purpose. 
    File: Matched_MinimumDeviceTree.csv

Once our we matched the corresponding devices from our device tree to the devices minimum list given, we moved on to determining what remaining devices in the device tree should be kept or removed. It could be inferred from some of the devices given in the minimum device tree what groups of components would be used or not. For example, all full-power domain (FPD) DMA channels are listed in the minimum device tree, so we assumed that the low-power domain (LPD) DMA channels would not be used. If two devices were present that performed similar functionality, but one was better than other, we kept the more proficient device.
    File: List of Devices and Their Functionality.pdf

We provide a final list of removed devices. 
    File: Removed_Devices.txt

The final device tree can be found in the Removing_Devices section of this repo.
    