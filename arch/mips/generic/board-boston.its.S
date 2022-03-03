/ {
	images {
<<<<<<< HEAD
		fdt@boston {
=======
		fdt-boston {
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
			description = "img,boston Device Tree";
			data = /incbin/("boot/dts/img/boston.dtb");
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
		conf@boston {
			description = "Boston Linux kernel";
			kernel = "kernel@0";
			fdt = "fdt@boston";
=======
		conf-boston {
			description = "Boston Linux kernel";
			kernel = "kernel";
			fdt = "fdt-boston";
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
		};
	};
};
