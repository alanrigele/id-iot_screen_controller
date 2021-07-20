INSERT INTO idiot.pallet_events (plant_id,site_id,dt,id,event_type,event_data) VALUES
	 (2,1,'2021-04-30 11:23:04','1','qa','p'),
	 (2,1,'2021-04-30 11:23:06','2','qa','p'),
	 (2,1,'2021-04-30 11:23:07','3','qa','p'),
	 (2,1,'2021-04-30 11:23:09','4','qa','p'),
	 (2,1,'2021-04-30 11:23:10','5','qa','p'),
	 (2,1,'2021-04-30 11:23:11','6','qa','p');INSERT INTO idiot.plant_message (plant_id,site_id,top_msg,bot_msg) VALUES
	 (1,1,'Top','Bottom'),
	 (2,1,'jhkgjhgjhg','jhgjhg'),
	 (2,1,'jhkgjhgjhg','jhgjhg'),
	 (3,1,NULL,NULL);INSERT INTO idiot.plants (plant_name,site_id) VALUES
	 ('Main Plant',1),
	 ('Distell',1),
	 ('Second Chep',1);INSERT INTO idiot.sites (site_name) VALUES
	 ('Elrode'),
	 ('PE');INSERT INTO idiot.table_message (plant_id,site_id,rpr_table_id,top_msg,bot_msg) VALUES
	 (2,1,1,'Hello ','Bob'),
	 (2,1,2,'Hello',NULL),
	 (2,1,3,'Good','Night'),
	 (2,1,4,'Sweet Dreams','Sue'),
	 (2,1,5,'MM','mm'),
	 (2,1,6,'1',NULL);INSERT INTO idiot.table_targets (plant_id,site_id,rpr_table_id,shift_type,target) VALUES
	 (2,1,3,'D','130'),
	 (2,1,4,'D','144'),
	 (2,1,6,'D','150'),
	 (1,1,1,'D','130'),
	 (2,1,1,'D','160'),
	 (2,1,2,'D','150'),
	 (2,1,5,'D','130');