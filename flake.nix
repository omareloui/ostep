{
  description = "OSTEP exercises";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = with pkgs; [
        gcc
        bear
        gnumake
        gdb
        valgrind
      ];

      shellHook = ''
        export SHELL=${pkgs.zsh}/bin/zsh
        exec $SHELL
      '';

      CPATH = "${pkgs.glibc.dev}/include";
    };
  };
}
