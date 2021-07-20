-- idiot.pallet_events definition

-- Drop table

-- DROP TABLE idiot.pallet_events;

CREATE TABLE idiot.pallet_events (
	event_id int8 NOT NULL DEFAULT nextval('idiot.pallet_event_seq'::regclass),
	plant_id int8 NULL,
	site_id int8 NULL,
	dt timestamp(0) NULL,
	id varchar NULL,
	event_type varchar NULL,
	event_data varchar NULL
);


-- idiot.plant_message definition

-- Drop table

-- DROP TABLE idiot.plant_message;

CREATE TABLE idiot.plant_message (
	plant_id int8 NULL,
	site_id int8 NULL,
	top_msg varchar(16) NULL,
	bot_msg varchar(16) NULL
);


-- idiot.plants definition

-- Drop table

-- DROP TABLE idiot.plants;

CREATE TABLE idiot.plants (
	plant_id int8 NOT NULL DEFAULT nextval('idiot.plant_id_seq'::regclass),
	plant_name varchar NULL,
	site_id int8 NULL
);
CREATE INDEX plants_plant_id_idx ON idiot.plants USING btree (plant_id);
CREATE INDEX plants_plant_site_id_idx ON idiot.plants USING btree (plant_id, site_id);


-- idiot.shifts definition

-- Drop table

-- DROP TABLE idiot.shifts;

CREATE TABLE idiot.shifts (
	shift_id int8 NOT NULL DEFAULT nextval('idiot.shift_id_seq'::regclass),
	site_id int8 NULL,
	plant_id int8 NULL,
	start_dt timestamp(0) NULL,
	end_dt timestamp(0) NULL
);


-- idiot.sites definition

-- Drop table

-- DROP TABLE idiot.sites;

CREATE TABLE idiot.sites (
	site_id int8 NOT NULL DEFAULT nextval('idiot.site_id_seq'::regclass),
	site_name varchar NULL
);


-- idiot.table_message definition

-- Drop table

-- DROP TABLE idiot.table_message;

CREATE TABLE idiot.table_message (
	plant_id int8 NULL,
	site_id int8 NULL,
	rpr_table_id int8 NULL,
	top_msg varchar(16) NULL,
	bot_msg varchar(16) NULL
);
CREATE INDEX table_message_rpr_table_id_idx ON idiot.table_message USING btree (rpr_table_id);


-- idiot.table_targets definition

-- Drop table

-- DROP TABLE idiot.table_targets;

CREATE TABLE idiot.table_targets (
	plant_id int8 NULL,
	site_id int8 NULL,
	rpr_table_id int8 NULL,
	shift_type varchar(10) NULL,
	target varchar(16) NULL
);
