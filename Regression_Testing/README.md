After removing a device from the device tree, we need to verify that a device identified for removal should actually be removed and won't cause any functionality to break. To this end, we perform regression testing for each of the removed devices; each member in the team performs testing for the subset of devices they were assigned. 

In the course of my approach to removing the devices I was assigned, I iterated through a few different testing strategies:
    
    Track the dependencies on a removed device (through this device's device_links, which is a Linux data structure that keeps track of other devices that are either dependent upon this device or that this device is dependent on) and perform testing on each of the dependent devices to ensure they remain functional
        Issue: testing each of these is redundant if we can just verify that the removed device itself is not functional

    Due to the complexity and time required to fully understand what a device does in depth, I attempt to utilize pre-built test suites and, if needed, create my own tests under their frameworks. I performed some initial research into using these various testing frameworks: 
        Kunit tests - utilized for kernel-space white-box testing
        kselftests - utilized for user-space testing that treats the kernel as a black-box 
        Linux Test Project - a collection of test suites that tests various subsystems of Linux
        Various sanitizers (address, concurrency, etc) and other kernel analysis tools

    From these I chose to further pursue:
        Kunit, because a pre-made script is provided that runs all tests easily for you
        Linux Test Project, because the breadth of tests, inclusion of some specific tests for hardware, and ease of use made it an attractive option

After receiving the hardware board that will be used for the final product and successfully booting on it, an initial run of Kunit tests did not work, but an initial run of Linux Test Project did work. I expected the debugging process for Kunit tests to take some substantial time, because Kunit test suites are spread throughout the kernel, and the version of Linux that is run on the hardware board we received is Xilinx Linux. I am not familiar with either the structure of Kunit tests or the differences between Xilinx Linux and standard Linux, and given the breadth of the Linux Test Project, I deemed the effort to get Kunit tests to work (if they even could) on Xilinx Linux not necessary enough to be worth it.

I go further into further detail of the Linux Test Project in the section I designate for it here.

Although I found the Linux Test project to be useful for some hardware devices, for the specific devices I was assigned to test, I found that the most useful existing test suites only tested the device's functionality by proxy. The Linux Test Project main objective seems to be regression testing for end use cases in Linux, and not thorough tests of individual components, including hardware components. Thus, I moved on to see if there were any other existing test suites specic to devices I was assigned to remove. 

One option I did find was from Xilinx itself, which offered thorough tests for the specific DMA channels I was assigned to remove through a kernel module called dmatest. The process and results from this test suite are included in a section designated here. 

All tests pass for the FPD DMA after the LPD is verifiably removed, and thus I conclude that the proper DMA channels have been successfuly removed.

    
