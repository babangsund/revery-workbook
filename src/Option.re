let map = f =>
  fun
  | Some(x) => Some(f(x))
  | None => None;

let value = (~default) =>
  fun
  | Some(x) => x
  | None => default;

let none = _ => None;

let some = x => Some(x);