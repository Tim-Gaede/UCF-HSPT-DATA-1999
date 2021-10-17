(***************************************************************************)
(*                      University of Central Florida                      *)
(*                            Thirteenth Annual                            *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(*                              May 7, 1999                                *)
(*                                                                         *)
(*                                                                         *)
(*                                                                         *)
(*                                                                         *)
(* Problem Name: The Y-to-K Problem                                        *)
(* Filename: YTOK                                                          *)
(*                                                                         *)
(* Specification by: Phillip Dexheimer                                     *)
(* Judge Solution and Data by: Ambrose Feinstein                           *)
(*                                                                         *)
(***************************************************************************)


{ ytok.pas

  this program is very simple (although hard to see under all those
  comments).  first it puts the input file on stdin, which makes reading
  from it very convenient.  then it reads characters until it reaches
  end of file.  for each character read, it translates it if necessary,
  and then writes it to stdout.  newlines and other whitespace pass
  through unchanged.
}

var
  c: char;
begin
  assign(input,'ytok.in'); { we dont need to read from the keyboard anyway }
  reset(input); { so for our convenience, open the input file on stdin }
  while not eof do begin { until end of file }
    read(c); { get a character }
    if c='y' then c:='k'; { translate it if necessary }
    if c='Y' then c:='K'; { ... }
    write(c); { write it to stdout }
  end;
  { eof reached, all done writing }
  flush(output); close(output); { paranoia }
end.
