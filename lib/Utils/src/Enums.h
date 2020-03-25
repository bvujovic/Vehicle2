#pragma once

// Dodatne opcije za komandu motorima.
enum MotCmdFlags
{
    // Bataljuje sve komande koje su na redu za izvrsavanje (i tekucu) i izvrsava se umesto njih.
    //* Mozda umesto ovog flaga dodati metod AddBreakingCmd
    Breaking = 1,
    // Kocenje
    Brake = 2,
    //? StandBy = 4 
    //? Cancelled // moze da bude korisno za nekakve izvestaje da bi se znalo da li su neke komande cancel-ovane
};