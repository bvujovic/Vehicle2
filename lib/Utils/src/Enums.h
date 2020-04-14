#pragma once

// Dodatne opcije za komandu motorima.
enum MotCmdFlags
{
    // Bataljuje sve komande koje su na redu za izvrsavanje (i tekucu) i izvrsava se umesto njih.
    Breaking = 1, //* Mozda umesto ovog flaga dodati metod AddBreakingCmd
    // Kocenje
    Brake = 2,

    //? TurnInPlace = 4 // Obrtanje vozila u mestu
    //? StandBy
    //? Cancelled // moze da bude korisno za nekakve izvestaje da bi se znalo da li su neke komande cancel-ovane
};