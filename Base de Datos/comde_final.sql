-- MariaDB dump 10.17  Distrib 10.4.8-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: basecalidad
-- ------------------------------------------------------
-- Server version	10.4.8-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `alumno`
--

DROP TABLE IF EXISTS `alumno`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alumno` (
  `idAlumno` varchar(35) NOT NULL,
  `nombreAlumno` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `claveEstado` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL,
  PRIMARY KEY (`idAlumno`),
  KEY `idCurso` (`idCurso`),
  KEY `idArea` (`idArea`),
  KEY `claveEstado` (`claveEstado`),
  KEY `idSeccion` (`idSeccion`),
  CONSTRAINT `alumno_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `alumno_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`),
  CONSTRAINT `alumno_ibfk_3` FOREIGN KEY (`claveEstado`) REFERENCES `estado` (`claveEstado`),
  CONSTRAINT `alumno_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `alumno`
--

LOCK TABLES `alumno` WRITE;
/*!40000 ALTER TABLE `alumno` DISABLE KEYS */;
INSERT INTO `alumno` VALUES ('1','Jorge','Molina','Lechuga',1,1,1,1),('2','Oliver','Viveroz','Juárez',2,2,1,1),('3','Tony','Paniagua','Ramos',3,1,1,1),('4','esteban','ghi','ghi',4,1,1,1),('5','dana','jkl','jkl',5,1,1,1),('6','Luis Angel','Amador','Ortiz',6,1,1,1),('7','Isma','Mendez','Suarez',5,1,1,1),('8','Isma','Mendez','Suarez',6,1,1,1);
/*!40000 ALTER TABLE `alumno` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `area_deportiva`
--

DROP TABLE IF EXISTS `area_deportiva`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `area_deportiva` (
  `idArea` int(11) NOT NULL,
  `nombreArea` varchar(50) NOT NULL,
  PRIMARY KEY (`idArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `area_deportiva`
--

LOCK TABLES `area_deportiva` WRITE;
/*!40000 ALTER TABLE `area_deportiva` DISABLE KEYS */;
INSERT INTO `area_deportiva` VALUES (1,'Deportes de Combate'),(2,'Escuela de Gimnasia'),(3,'Centro Acuatico');
/*!40000 ALTER TABLE `area_deportiva` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `asistencia`
--

DROP TABLE IF EXISTS `asistencia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `asistencia` (
  `asisID` int(11) NOT NULL AUTO_INCREMENT,
  `alumnoID` int(11) NOT NULL,
  `cursoID` int(11) NOT NULL,
  `horarioID` int(11) NOT NULL,
  `fecha` date DEFAULT NULL,
  `presente` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`asisID`),
  KEY `alumnoID` (`alumnoID`),
  KEY `cursoID` (`cursoID`),
  KEY `horarioID` (`horarioID`),
  CONSTRAINT `asistencia_ibfk_2` FOREIGN KEY (`cursoID`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `asistencia_ibfk_3` FOREIGN KEY (`horarioID`) REFERENCES `horario` (`idHorario`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asistencia`
--

LOCK TABLES `asistencia` WRITE;
/*!40000 ALTER TABLE `asistencia` DISABLE KEYS */;
INSERT INTO `asistencia` VALUES (1,1,1,1,'2019-10-23',1),(2,2,1,1,'2019-10-23',1),(3,3,1,1,'2019-10-23',0),(4,4,1,1,'2019-10-23',0),(5,5,1,1,'2019-10-23',1),(6,6,6,6,'2019-10-23',1);
/*!40000 ALTER TABLE `asistencia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `curso`
--

DROP TABLE IF EXISTS `curso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `curso` (
  `idCurso` int(11) NOT NULL,
  `matriculaProfesor` varchar(35) NOT NULL,
  `idHorario` int(11) NOT NULL,
  `idLocacion` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL,
  PRIMARY KEY (`idCurso`),
  KEY `matriculaProfesor` (`matriculaProfesor`),
  KEY `idHorario` (`idHorario`),
  KEY `idLocacion` (`idLocacion`),
  KEY `idSeccion` (`idSeccion`),
  CONSTRAINT `curso_ibfk_1` FOREIGN KEY (`matriculaProfesor`) REFERENCES `trabajador` (`matricula`),
  CONSTRAINT `curso_ibfk_2` FOREIGN KEY (`idHorario`) REFERENCES `horario` (`idHorario`),
  CONSTRAINT `curso_ibfk_3` FOREIGN KEY (`idLocacion`) REFERENCES `locacion` (`idLocacion`),
  CONSTRAINT `curso_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `curso`
--

LOCK TABLES `curso` WRITE;
/*!40000 ALTER TABLE `curso` DISABLE KEYS */;
INSERT INTO `curso` VALUES (1,'100034438',1,1,1),(2,'100034439',2,3,2),(3,'100034437',1,3,1),(4,'100034440',2,2,1),(5,'12345',5,1,1),(6,'12345',6,1,1);
/*!40000 ALTER TABLE `curso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `curso_abierto`
--

DROP TABLE IF EXISTS `curso_abierto`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `curso_abierto` (
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `nombreCurso` varchar(45) NOT NULL,
  KEY `idCurso` (`idCurso`),
  KEY `idArea` (`idArea`),
  CONSTRAINT `curso_abierto_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `curso_abierto_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `curso_abierto`
--

LOCK TABLES `curso_abierto` WRITE;
/*!40000 ALTER TABLE `curso_abierto` DISABLE KEYS */;
INSERT INTO `curso_abierto` VALUES (1,1,'Karate Do'),(2,2,'Gimnasia Infantil'),(3,3,'Natacion para principiantes'),(4,3,'Natacion Avanzada');
/*!40000 ALTER TABLE `curso_abierto` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `estado`
--

DROP TABLE IF EXISTS `estado`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `estado` (
  `claveEstado` int(11) NOT NULL,
  `descripcionEstado` varchar(50) NOT NULL,
  PRIMARY KEY (`claveEstado`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `estado`
--

LOCK TABLES `estado` WRITE;
/*!40000 ALTER TABLE `estado` DISABLE KEYS */;
INSERT INTO `estado` VALUES (1,'activo');
/*!40000 ALTER TABLE `estado` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `horario`
--

DROP TABLE IF EXISTS `horario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `horario` (
  `idHorario` int(11) NOT NULL,
  `hora_inicio` time NOT NULL,
  `hora_final` time NOT NULL,
  PRIMARY KEY (`idHorario`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `horario`
--

LOCK TABLES `horario` WRITE;
/*!40000 ALTER TABLE `horario` DISABLE KEYS */;
INSERT INTO `horario` VALUES (1,'09:00:00','11:00:00'),(2,'11:00:00','12:00:00'),(3,'08:00:00','11:59:59'),(4,'12:00:00','15:59:59'),(5,'16:00:00','19:59:59'),(6,'20:00:00','24:59:59');
/*!40000 ALTER TABLE `horario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `locacion`
--

DROP TABLE IF EXISTS `locacion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `locacion` (
  `idLocacion` int(11) NOT NULL,
  `lugar` varchar(50) NOT NULL,
  PRIMARY KEY (`idLocacion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `locacion`
--

LOCK TABLES `locacion` WRITE;
/*!40000 ALTER TABLE `locacion` DISABLE KEYS */;
INSERT INTO `locacion` VALUES (1,'Dojo Karate COMDE'),(2,'Centro Acuatico COMDE'),(3,'Centro de Gimnasia COMDE');
/*!40000 ALTER TABLE `locacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nivel_trabajador`
--

DROP TABLE IF EXISTS `nivel_trabajador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `nivel_trabajador` (
  `nivelTrabajador` int(11) NOT NULL,
  `puesto` varchar(50) NOT NULL,
  PRIMARY KEY (`nivelTrabajador`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nivel_trabajador`
--

LOCK TABLES `nivel_trabajador` WRITE;
/*!40000 ALTER TABLE `nivel_trabajador` DISABLE KEYS */;
INSERT INTO `nivel_trabajador` VALUES (1,'Administrador General'),(2,'Administrador de Area'),(3,'Profesor');
/*!40000 ALTER TABLE `nivel_trabajador` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `profesor`
--

DROP TABLE IF EXISTS `profesor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `profesor` (
  `matricula` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  PRIMARY KEY (`matricula`),
  KEY `idCurso` (`idCurso`),
  KEY `idArea` (`idArea`),
  CONSTRAINT `profesor_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `profesor_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `profesor`
--

LOCK TABLES `profesor` WRITE;
/*!40000 ALTER TABLE `profesor` DISABLE KEYS */;
/*!40000 ALTER TABLE `profesor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `seccion`
--

DROP TABLE IF EXISTS `seccion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seccion` (
  `idSeccion` int(11) NOT NULL,
  `descripcion` varchar(250) NOT NULL,
  PRIMARY KEY (`idSeccion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `seccion`
--

LOCK TABLES `seccion` WRITE;
/*!40000 ALTER TABLE `seccion` DISABLE KEYS */;
INSERT INTO `seccion` VALUES (1,'Seccion 1'),(2,'Seccion 2');
/*!40000 ALTER TABLE `seccion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trabajador`
--

DROP TABLE IF EXISTS `trabajador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trabajador` (
  `matricula` varchar(35) NOT NULL,
  `nombre` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `correoE` varchar(60) NOT NULL,
  `celular` varchar(13) DEFAULT NULL,
  `edad` int(11) NOT NULL,
  `contrasegna` varchar(30) NOT NULL,
  `nivel` int(11) NOT NULL,
  PRIMARY KEY (`matricula`),
  KEY `nivel` (`nivel`),
  CONSTRAINT `trabajador_ibfk_1` FOREIGN KEY (`nivel`) REFERENCES `nivel_trabajador` (`nivelTrabajador`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trabajador`
--

LOCK TABLES `trabajador` WRITE;
/*!40000 ALTER TABLE `trabajador` DISABLE KEYS */;
INSERT INTO `trabajador` VALUES ('100034433','Esteban','Calixto','Cruz','esteban_calixto_cruz4@hotmail.com','2321259246',25,'1728',1),('100034434','Sandra','Rosas','Ortega','sandra@gmail.com','2321259247',25,'12345',2),('100034435','Jiuber','Monfil','Quijano','Jiuber@gmail.com','2321259248',25,'12345',2),('100034436','Juan ','Flores ','Cabañas','Juanpi@hotmail.com','2321259249',25,'12345',2),('100034437','Jorge','Lopez','Aragon','Alucard@gmail.com','2321259250',25,'12345',3),('100034438','Laura','Villarreal ','Onofre','lauraV@gmail.com','2321259251',25,'12345',3),('100034439','Yecxalin','Cobos','Tejeda','yecxa@hotmail.com','2321259252',25,'12345',3),('100034440','Carla','Sofia','Alarcon','Santiago@hotmail.com','2321259253',25,'12345',3),('100034441','Juan','Luna','Ojeda','luna@hotmail.com','2321259253',25,'12345',3),('100034442','Ana','Julian','Garcia','acuario@gmail.com','2321259254',25,'12345',3),('100034443','Jorge','Hernandez','Baltazar','jHernandez@gmail.com','2321259255',25,'12345',3),('100034444','Hector','Celis','Cabrera','hectorM@hotmail.com','2321259256',25,'12345',3),('100034445','Bryan','Celis','Cabrera','bryan@gmail.com','2321259257',25,'12345',3),('12345','tony','paniagua','ramos','tony@gmail.com','2229200704',22,'123',1);
/*!40000 ALTER TABLE `trabajador` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-11-11 16:43:34
