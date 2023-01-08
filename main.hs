module Main where 
import Data.Foldable
import Control.Applicative

-- natürliche Bäume 

data NatBaum e = NatLeer | NatZweig (NatBaum e) e (NatBaum e) deriving (Show, Eq)

insert :: Ord o => o -> NatBaum o -> NatBaum o
insert e NatLeer = NatZweig NatLeer e NatLeer
insert e (NatZweig l a r)
  | e < a = NatZweig (insert e l) a r
  | e >= a = NatZweig l a (insert e r)

instance Foldable NatBaum where 
  foldr f init NatLeer = init
  foldr f init (NatZweig l e r) = foldr f (f e (foldr f init r)) l

findMin :: NatBaum a -> a
findMin a = head (toList a)

instance Functor NatBaum where 
  fmap f NatLeer = NatLeer 
  fmap f (NatZweig l e r) = NatZweig (f <$> l) (f e) (f <$> r)

instance Traversable NatBaum where 
  traverse appl NatLeer = pure NatLeer
  traverse appl (NatZweig l e r) = liftA3 NatZweig (traverse appl l) (appl e) (traverse appl r)


main = print $ traverse (\n -> if odd n then Nothing else Just n) $ insert 0 $ insert 4 $ insert 2 NatLeer
