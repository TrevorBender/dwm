{
  description = "A Nix-flake-based C/C++ development environment";

  inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    devShells.${system}.default =
      pkgs.mkShell
      {
        packages = with pkgs; [
          xorg.libX11
          xorg.libXft
          xorg.libXinerama
          clang-tools
          gdb
        ];
      };
  };
}
