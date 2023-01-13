-- Keep a log of any SQL queries you execute as you solve the mystery.

-- let's first check the crime_scene_reports based on the known data
-- the theft took place in the Humphrey Street bakery on July 28, 2021
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- get more information from the interviews, now we know...
-- ...the thief withdraw money.
-- ...they called someone (less than a minute). the other person will buy the flight ticket.
-- ...they plan to take the earlist flight tomorrow July 29, 2021
SELECT * from interviews WHERE year = 2021 AND month = 7 AND day = 28;

-- from previous query we know
-- the theft took place on July 28, 2021 at 10:15am at the Humphrey Street bakery (minute 14 -> entrance, minute 16 -> exit, minute 15 -> no info)
-- interview => Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- with previouns information...

-- ...we can find license plates from the bakery as in the interview was said "I was the thief get into a car..."
SELECT name, phone_number, passport_number
FROM people WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021
     AND month = 7
     AND day = 28
     AND hour = 10
     AND minute >= 15
     AND minute <= 25
     );

-- ...we can find names of suspects based on interview's sentences " the thief withdraw money on Leggett Street"
SELECT p.name, atm.transaction_type
FROM people AS p
    INNER JOIN bank_accounts AS b
    ON b.person_id = p.id

    INNER JOIN atm_transactions AS atm
    ON atm.account_number = b.account_number
    WHERE atm.year = 2021
     AND atm.month = 7
     AND atm.day = 28
     AND atm.atm_location = "Leggett Street"
     AND atm.transaction_type = "withdraw"
    ;

-- ...they called someone (less than a minute). the other person will buy the flight ticket.
 UPDATE phone_calls AS pc
 SET c_name = p.name
 FROM people as p
 WHERE pc.caller = p.phone_number;

 UPDATE phone_calls AS pc
 SET r_name = p.name
 FROM people as p
 WHERE pc.receiver = p.phone_number;

 SELECT caller, c_name, receiver, r_name
FROM phone_calls
WHERE year = 2021
 AND month = 7
 AND day = 28
 AND duration < 60;

--...they plan to take the earlist flight tomorrow July 29, 2021
SELECT id, hour, minute, origin_airport_id, destination_airport_id
FROM flights
WHERE year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1;

UPDATE flights AS f
SET origin_airport_id = a.city
FROM airports AS a
WHERE f.origin_airport_id = a.id;

UPDATE flights AS f
SET destination_airport_id = a.city
FROM airports AS a
WHERE f.destination_airport_id = a.id;

-- And finally we can pick up all the previous necessary queiryes and mix them in one big-mix-huge query to find it out!
SELECT f.destination_airport_id, p.name, p.phone_number, p.license_plate FROM people AS p
INNER JOIN passengers AS pa ON pa.passport_number = p.passport_number
INNER JOIN flights AS f ON f.id = pa.flight_id
WHERE (f.id = 36 AND f.year = 2021 AND f.month = 7 AND f.day = 29)
AND p.name IN (
    SELECT p_c.c_name FROM phone_calls AS p_c
    WHERE p_c.year = 2021
     AND p_c.month = 7
     AND p_c.day = 28
     AND p_c.duration < 60
    )
AND p.name IN (
    SELECT p.name FROM people AS p
    INNER JOIN bank_accounts AS b
    ON b.person_id = p.id

    INNER JOIN atm_transactions AS atm
    ON atm.account_number = b.account_number
    WHERE atm.year = 2021
     AND atm.month = 7
     AND atm.day = 28
     AND atm.atm_location = "Leggett Street"
     AND atm.transaction_type = "withdraw"
)
AND p.name IN (
    SELECT p.name FROM people AS p
    INNER JOIN bakery_security_logs AS bsl ON bsl.license_plate = p.license_plate
    WHERE bsl.year = 2021
     AND bsl.month = 7
     AND bsl.day = 28
     AND bsl.minute >= 15
     AND bsl.minute <= 25
);