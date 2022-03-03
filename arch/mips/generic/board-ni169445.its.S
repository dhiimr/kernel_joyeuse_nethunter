/ {
	images {
<<<<<<< HEAD
		fdt@ni169445 {
=======
		fdt-ni169445 {
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			description = "NI 169445 device tree";
			data = /incbin/("boot/dts/ni/169445.dtb");
			type = "flat_dt";
			arch = "mips";
			compression = "none";
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
		conf@ni169445 {
			description = "NI 169445 Linux Kernel";
			kernel = "kernel@0";
			fdt = "fdt@ni169445";
=======
		conf-ni169445 {
			description = "NI 169445 Linux Kernel";
			kernel = "kernel";
			fdt = "fdt-ni169445";
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		};
	};
};
