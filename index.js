const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const Pool = require("pg").Pool;
const pool = new Pool({
  user: "postgres",
  host: "192.168.1.55",
  database: "postgres",
  password: "postgres",
  port: 5432
});

const app = express();

app.use(cors());
app.use(bodyParser.json());

app.get("/api/v1/screens_1_2", (req, res) => {
  pool.query(
    "SELECT * FROM idiot.screens_1_2 order by site_id, plant_id, rpr_table_id",
    [],
    (error, results) => {
      if (error) {
              console.log("Error: ",error);
        throw error;
      }
        console.log("Responded");
      res.status(200).json(results.rows);
    }
  );
});

app.get("/api/v1/screens", (req, res) => {
  pool.query(
    "SELECT * FROM idiot.screens order by site_id, plant_id, rpr_table_id",
    [],
    (error, results) => {
      if (error) {
              console.log("Error: ",error);
        throw error;
      }
        console.log("Responded");
      res.status(200).json(results.rows);
    }
  );
});



app.get("/api/v1/screens/:site", (req, res) => {
  pool.query(
    "SELECT * FROM idiot.screens where site_id = " + req.params.siteid + "order by site_id, plant_id, rpr_table_id" ,
    [],
    (error, results) => {
      if (error) {
	      console.log("Error: ",error);
        throw error;	
      }
	console.log("Responded");
      res.status(200).json(results.rows);
    }
  );
});

app.get("/api/v1/screens/:siteid/:plantid", (req, res) => {
  pool.query(
    "SELECT * FROM idiot.screens  where site_id = " + req.params.siteid + " and plant_id = " + req.params.siteid + "order by site_id, plant_id, rpr_table_id",
    [],
    (error, results) => {
      if (error) {
	      console.log("Error: ",error);
        throw error;	
      }
	console.log("Responded");
      res.status(200).json(results.rows);
    }
  );
});

app.get("/api/v1/screens/:siteid/:plantid/:tableid", (req, res) => {
  pool.query(
    "SELECT * FROM idiot.screens  where site_id = " + req.params.siteid + " and plant_id = " + req.params.siteid + " and rpr_table_id = " + req.params.tableid + " order by site_id, plant_id, rpr_table_id",
    [],
    (error, results) => {
      if (error) {
	      console.log("Error: ",error);
        throw error;	
      }
	console.log("Responded");
      res.status(200).json(results.rows);
    }
  );
});


app.listen(8000, () => {
  console.log(`Server is running.`);
});
