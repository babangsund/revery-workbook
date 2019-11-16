open Lwt.Infix;

open Yojson;
open Yojson.Basic;
open Yojson.Basic.Util;

open Fetch;
open Fetch.Response;

let baseUrl = "http://workbook.HOSTNAME.com/api";
let toText = r => r.text();

let employeeUrl = baseUrl ++ "/resource/employees?Active=true";
let fetchEmployees = fetch(employeeUrl) >>= toText;