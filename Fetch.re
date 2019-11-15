open Lwt;
open Cohttp;
open Cohttp_lwt_unix;
module Cohttp_Response = Response;

type method =
  | Get
  | Post;

module Response = {
  type t = {
    status: int,
    text: unit => Lwt.t(string),
  };
};

let fetch =
    (
      ~method=Get,
      ~user: string,
      ~pass: string,
      ~body=Cohttp_lwt.Body.empty,
      url: string,
    ) => {
  let headers =
    Header.init()
    |> (
      h =>
        Header.add_list(
          h,
          [
            ("Accept", "application/json"),
            ("Content-Type", "application/json"),
            (
              "Authorization",
              "Basic " ++ Base64.encode_string(user ++ ":" ++ pass),
            ),
          ],
        )
    );

  let action =
    switch (method) {
    | Get => Client.get(Uri.of_string(url), ~headers)
    | Post => Client.post(Uri.of_string(url), ~headers, ~body)
    };

  let callback = ((resp, body)) => {
    let status = resp |> Cohttp_Response.status |> Code.code_of_status;
    let readText = (body, ()) => Cohttp_lwt.Body.to_string(body);
    Lwt.return(Response.{status, text: readText(body)});
  };

  Lwt.bind(action, callback);
};