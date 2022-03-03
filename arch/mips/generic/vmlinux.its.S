/* SPDX-License-Identifier: GPL-2.0 */
/dts-v1/;

/ {
	description = KERNEL_NAME;
	#address-cells = <ADDR_CELLS>;

	images {
<<<<<<< HEAD
		kernel@0 {
=======
		kernel {
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			description = KERNEL_NAME;
			data = /incbin/(VMLINUX_BINARY);
			type = "kernel";
			arch = "mips";
			os = "linux";
			compression = VMLINUX_COMPRESSION;
			load = /bits/ ADDR_BITS <VMLINUX_LOAD_ADDRESS>;
			entry = /bits/ ADDR_BITS <VMLINUX_ENTRY_ADDRESS>;
<<<<<<< HEAD
			hash@0 {
=======
			hash {
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
				algo = "sha1";
			};
		};
	};

	configurations {
<<<<<<< HEAD
		default = "conf@default";

		conf@default {
			description = "Generic Linux kernel";
			kernel = "kernel@0";
=======
		default = "conf-default";

		conf-default {
			description = "Generic Linux kernel";
			kernel = "kernel";
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		};
	};
};
