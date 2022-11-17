
$fn=60;
difference() {
			hull() {
			translate ([0,0,0]) cylinder (r=5.5,h=3);
			translate ([31,0,0]) cylinder (r=5.5,h=3);
			translate ([0,31,0]) cylinder (r=5.5,h=3);
			translate ([31,31,0]) cylinder (r=5.5,h=3);
			}

		translate ([0,0,-1]) cylinder (r=1.7,h=4);
		translate ([31,0,-1]) cylinder (r=1.7,h=4);
		translate ([0,31,-1]) cylinder (r=1.7,h=4);
		translate ([31,31,-1]) cylinder (r=1.7,h=4);

	translate ([15.5,15.5,-1]) cylinder (r=12,h=4);	
}
