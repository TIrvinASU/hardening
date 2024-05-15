Devices are removed from the device tree through deletion instead of setting their status to disabled, which makes for cleaner code. To delete a device in the device tree, in general you need to alter the .dts (stands for device tree source) file; in a Petalinux project specifically, changes to the device tree are included through an alteration of the system-conf.dtsi, which is included in the final .dts that Petalinux builds. A final copy of this file is included.
    File: System-user.dtsi

To verify if a device has been removed, we verify through reassembling the .dtb (device tree blob) and greping it for the relevant device or look at relevant directories at runtime.

The final device tree blob with the proper devices removed has been included.
    File: System-top.dtb