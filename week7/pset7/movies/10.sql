SELECT DISTINCT name
FROM people
    JOIN directors ON people.id = directors.person_id
    JOIN movies ON movies.id = directors.movie_id
    JOIN ratings ON ratings.movie_id = movies.id
    WHERE rating >= 9.0;