CREATE TABLE reports_tb (
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    type VARCHAR (15) NOT NULL,
    value_1 INTEGER NOT NULL,
    value_2 INTEGER NOT NULL,
    result INTEGER NOT NULL,
    data INTEGER NOT NULL
);