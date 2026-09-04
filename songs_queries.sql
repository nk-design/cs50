-- List the ten most danceable songs, most danceable first
SELECT name, artist, danceability
FROM songs
ORDER BY danceability DESC
LIMIT 10;

-- List all songs by "The Weeknd", most energetic first
SELECT name, energy
FROM songs
WHERE artist = 'The Weeknd'
ORDER BY energy DESC;

-- Average valence (musical positiveness) across all songs
SELECT AVG(valence) AS average_valence
FROM songs;

-- Songs longer than 3.5 minutes (210000 ms), fastest tempo first
SELECT name, artist, duration_ms, tempo
FROM songs
WHERE duration_ms > 210000
ORDER BY tempo DESC;
