/*
 Navicat Premium Data Transfer

 Source Server         : global
 Source Server Type    : SQLite
 Source Server Version : 3017000
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3017000
 File Encoding         : 65001

 Date: 27/12/2019 18:05:05
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for smoking
-- ----------------------------
DROP TABLE IF EXISTS "smoking";
CREATE TABLE "smoking" (
  "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  "name" TEXT,
  "bar_code" TEXT
);

-- ----------------------------
-- Records of "smoking"
-- ----------------------------
INSERT INTO "smoking" VALUES (1, '烟草1', 6901028207041);
INSERT INTO "smoking" VALUES (2, '烟草2', 6901028207042);
INSERT INTO "smoking" VALUES (3, '烟草3', 6901028207043);
INSERT INTO "smoking" VALUES (4, '烟草4', 6901028207044);
INSERT INTO "smoking" VALUES (5, '烟草5', 6901028207045);
INSERT INTO "smoking" VALUES (6, '烟草6', 6901028207046);
INSERT INTO "smoking" VALUES (7, '烟草7', 6901028207047);
INSERT INTO "smoking" VALUES (8, '烟草8', 6901028207048);
INSERT INTO "smoking" VALUES (9, '烟草9', 6901028207049);
INSERT INTO "smoking" VALUES (10, '烟草10', 6901028207050);

-- ----------------------------
-- Auto increment value for smoking
-- ----------------------------
UPDATE "sqlite_sequence" SET seq = 63 WHERE name = 'smoking';

PRAGMA foreign_keys = true;
